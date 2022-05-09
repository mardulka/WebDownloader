#include "CFileHtml.h"

#include <utility>

using namespace std;

CFileHtml::CFileHtml(CUrl url, const string & relative_path)
        : CFile(std::move(url), relative_path, "html", CFileType::HTML){}

list<CUrl> CFileHtml::readLinks(){
    list<CUrl> links;

    string content_new;
    content_new.reserve(m_content.size() * 2);

    for (auto iter_str = m_content.begin() ; iter_str != m_content.end() ; content_new.push_back(*iter_str++)){
        //check if tag starts
        if (*iter_str != '<' || *(iter_str + 1) == '/')
            continue;

        //iterator on tag start
        auto iter_tag_start = iter_str + 1;

        //find ending '>' tag
        auto iter_tag_end = iter_tag_start;
        while (*iter_tag_end != '>')
            ++iter_tag_end;

        //find tag name
        auto iter_tag_name_end = iter_tag_start;
        while (*iter_tag_name_end != ' ' && *iter_tag_name_end != '>')
            ++iter_tag_name_end;
        string tag_name = string(iter_tag_start, iter_tag_name_end);

        //find tag attributes
        optional<pair<size_t, size_t >> link_limits;
        string tag_attributes = string(iter_tag_name_end, iter_tag_end);

        //find link in tags as position limits <a, b)
        if (tag_name == "a"){
            link_limits = findLinkInTag(tag_attributes, "href"s);
        } else if (tag_name == "img" || tag_name == "script"){
            link_limits = findLinkInTag(tag_attributes, "src"s);
        } else if (tag_name == "link"){
            link_limits = findLinkCss(tag_attributes);
        } else{
            content_new.append(string(iter_str, iter_tag_end));
            iter_str = iter_tag_end;
            continue;
        }

        //make absolute + add to links
        if (link_limits.has_value()){
            auto absolute_link = makeLinkAbsolute(
                    tag_attributes.substr(link_limits->first, link_limits->second - link_limits->first));
            if (!absolute_link.has_value())
                continue;
            tag_attributes.replace(link_limits->first, link_limits->second - link_limits->first, absolute_link.value());

            //insert into list for further return
            try{
                CUrl newlink(absolute_link.value());
                links.push_back(newlink);
            } catch (const invalid_argument & e){
                continue;
            }
        }

        //append modified tag
        content_new.append(string(iter_str, iter_tag_name_end)).append(tag_attributes);
        iter_str = iter_tag_end;
    }

    //swap content to new
    swap(m_content, content_new);

    return links;
}

void CFileHtml::replaceLinks(const std::unordered_map<std::string, std::filesystem::path> & replacing_map){
    string content_new;
    content_new.reserve(m_content.size() * 2);

    for (auto iter_str = m_content.begin() ; iter_str != m_content.end() ; content_new.push_back(*iter_str++)){
        //check if tag starts
        if (*iter_str != '<' || *(iter_str + 1) == '/')
            continue;

        //iterator on tag start
        auto iter_tag_start = iter_str + 1;

        //find ending '>' tag
        auto iter_tag_end = iter_tag_start;
        while (*iter_tag_end != '>')
            ++iter_tag_end;

        //find tag name
        auto iter_tag_name_end = iter_tag_start;
        while (*iter_tag_name_end != ' ' && *iter_tag_name_end != '>')
            ++iter_tag_name_end;
        string tag_name = string(iter_tag_start, iter_tag_name_end);

        //find tag attributes
        optional<pair<size_t, size_t >> link_limits;
        string tag_attributes = string(iter_tag_name_end, iter_tag_end);

        //find link in tags as position limits <a, b)
        if (tag_name == "a"){
            link_limits = findLinkInTag(tag_attributes, "href"s);
        } else if (tag_name == "img" || tag_name == "script"){
            link_limits = findLinkInTag(tag_attributes, "src"s);
        } else if (tag_name == "link"){
            link_limits = findLinkCss(tag_attributes);
        } else{
            content_new.append(string(iter_str, iter_tag_end));
            iter_str = iter_tag_end;
            continue;
        }

        //find in map and replace
        if (link_limits.has_value()){
            auto link = tag_attributes.substr(link_limits->first, link_limits->second - link_limits->first);
            auto path = replacing_map.find(link);
            if (path != replacing_map.end()){
                tag_attributes.replace(link_limits->first, link_limits->second - link_limits->first,
                                       filesystem::relative(path->second.parent_path(),
                                                            m_file_path.parent_path()).generic_string() /
                                       path->second.filename());
            }
        }
        //append modified tag
        content_new.append(string(iter_str, iter_tag_name_end)).append(tag_attributes);
        iter_str = iter_tag_end;
    }

    //swap content to new
    swap(m_content, content_new);
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkInTag(const string & tag, const string & attr_name_check){
    for (auto iter_str = tag.begin() ; iter_str != tag.end() ; ++iter_str){
        //skip first spaces
        if (*iter_str == ' '){
            continue;
        }

        //read attribute name
        auto iter_attr_name_end = iter_str;
        while (*iter_attr_name_end != '=')
            ++iter_attr_name_end;
        string attr_name = string(iter_str, iter_attr_name_end);

        //read attr content
        auto iter_attr_cont_start = iter_attr_name_end;
        while (*iter_attr_cont_start != '"')
            ++iter_attr_cont_start;
        ++iter_attr_cont_start; //move to first attr content letter

        auto iter_attr_cont_end = iter_attr_cont_start;
        while (*iter_attr_cont_end != '"')
            ++iter_attr_cont_end;
        string attr_content = string(iter_attr_cont_start, iter_attr_cont_end);

        //check attribute name - if found return limits
        if (attr_name == attr_name_check){
            //cout << "Found link {" << attr_content << "}" << endl;
            return make_pair(iter_attr_cont_start - tag.begin(), iter_attr_cont_end - tag.begin());
        }

        // no link found, move iterator to attribute end and try next attribute
        iter_str = iter_attr_cont_end;
    }

    //no src found, therefore empty optional returned
    return {};
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkCss(const string & tag){

    bool link = false;
    bool rel = false;
    pair<size_t, size_t> link_limits;

    for (auto iter_str = tag.begin() ; iter_str != tag.end() && (!link || !rel) ; ++iter_str){
        //skip first spaces
        if (*iter_str == ' '){
            continue;
        }

        //read attribute name
        auto iter_attr_name_end = iter_str;
        while (*iter_attr_name_end != '=')
            ++iter_attr_name_end;
        string attr_name = string(iter_str, iter_attr_name_end);

        //read attr content
        auto iter_attr_cont_start = iter_attr_name_end;
        while (*iter_attr_cont_start != '"')
            ++iter_attr_cont_start;
        ++iter_attr_cont_start; //move to first attr content letter

        auto iter_attr_cont_end = iter_attr_cont_start;
        while (*iter_attr_cont_end != '"')
            ++iter_attr_cont_end;
        string attr_content = string(iter_attr_cont_start, iter_attr_cont_end);

        //check attribute names
        if (attr_name == "href"s){
            link_limits = make_pair(iter_attr_cont_start - tag.begin(), iter_attr_cont_end - tag.begin());
            link = true;
        } else if (attr_name == "rel"s){
            if (attr_content == "stylesheet"s){
                rel = true;
            } else{
                break;
            }
        }

        // no link or rel found, move iterator to attribute end and try next attribute
        iter_str = iter_attr_cont_end;
    }

    //found link and correct rel
    if (rel && link){
        return link_limits;
    }

    //link not found or rel not correct
    return {};
}

void CFileHtml::generateName(const filesystem::path & targetFolder, set<std::filesystem::path> & used_names){
    //generate filename from host
    string filename_host = m_url.getHost();
    for (auto & item: filename_host){
        if (item == '.')
            item = '_';
    }

    //generate filename from path with cut first "/"
    auto filename_path = m_url.getPath().substr(1, m_url.getPath().size() - 1);
    for (auto & item: filename_path){
        if (item == '/')
            item = '_';
    }

    m_file_name = filename_host;
    if(!filename_path.empty())
        m_file_name.append("_" + filename_path);


    // if file is top level, it shouldn't be in sub-folder
    if (m_level == 0)
        m_relative_path = "";

    //create path, check if exists, if so give first free number behind name
    auto tmp_path = targetFolder / m_relative_path / (m_file_name + '.' + m_file_ending);
    for (int dist = 0 ; used_names.find(tmp_path) != used_names.end() ; ++dist){
        tmp_path = targetFolder / m_relative_path / (m_file_name + to_string(dist) + '.' + m_file_ending);
    }

    //save path in file
    m_file_path = tmp_path;

    //reserve name
    used_names.insert(m_file_path);

}

void CFileHtml::setContent(std::string content){
    m_content = std::move(content);

    //skip possible starting bytes
    auto iter = m_content.begin();
    while (*iter != '<')
        ++iter;

    //skip first
    if (iter != m_content.begin())
        m_content = string(iter, m_content.end());

}
