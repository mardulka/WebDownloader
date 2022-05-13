#include "CFileCss.h"

using namespace std;

CFileCss::CFileCss(CUrl url, const string & relative_path)
        : CFile(move(url), relative_path, "css", CFileType::CSS){}

list<CUrl> CFileCss::readLinks(){
    list<CUrl> links;

    string content_new;
    content_new.reserve(m_content.size());

    size_t pos = 0;
    size_t found_pos = 0;
    auto iter_copy_start = m_content.begin();
    //find url's in loop
    while ((found_pos = m_content.find("url("s, pos)) != string::npos){
        //copy previous content
        auto iter_link_start = m_content.begin() + found_pos + 4; //TODO may overflow
        content_new.append(string(iter_copy_start, iter_link_start));

        //get link
        char ending_char = ')';
        if (*iter_link_start == '"'){
            ending_char = '"';
            content_new.push_back(*(iter_link_start++));
        } else if (*iter_link_start == '\''){
            ending_char = '\'';
            content_new.push_back(*(iter_link_start++));
        }
        auto iter_link_end = iter_link_start;
        while (*iter_link_end != ending_char){
            ++iter_link_end;
        }
        string link(iter_link_start, iter_link_end);

        //make absolute
        auto absolute_link = makeLinkAbsolute(link);

        //check for "data:" link start, or no value of absolute link
        if (link.substr(0, 5) == "data:"s){
            content_new.append(link);
        } else if (!absolute_link.has_value()){
            content_new.append(link);
        } else{
            content_new.append(absolute_link.value());

            //insert into list for further return
            try{
                CUrl newlink(absolute_link.value());
                links.push_back(newlink);
            } catch (const invalid_argument & e){
                //continue;
            }
        }

        //move to find next
        pos = iter_link_end - m_content.begin();
        iter_copy_start = iter_link_end;
    }

    //copy rest
    content_new.append(string(iter_copy_start, m_content.end()));

    swap(m_content, content_new);

    return links;
}

void CFileCss::replaceLinks(const unordered_map<string, filesystem::path> & replacing_map){

    string content_new;
    content_new.reserve(m_content.size());

    size_t pos = 0;
    size_t found_pos = 0;
    auto iter_copy_start = m_content.begin();
    //find and replace url's in loop
    while ((found_pos = m_content.find("url("s, pos)) != string::npos){
        //copy previous content
        auto iter_link_start = m_content.begin() + found_pos + 4; //TODO may overflow
        content_new.append(string(iter_copy_start, iter_link_start));

        //get link
        char ending_char = ')';
        if (*iter_link_start == '"'){
            ending_char = '"';
            content_new.push_back(*(iter_link_start++));
        } else if (*iter_link_start == '\''){
            ending_char = '\'';
            content_new.push_back(*(iter_link_start++));
        }
        auto iter_link_end = iter_link_start;
        while (*iter_link_end != ending_char){
            ++iter_link_end;
        }
        string link(iter_link_start, iter_link_end);

        //find in map and replace
        auto path = replacing_map.find(link);
        if (path != replacing_map.end()){
            content_new.append(filesystem::relative(path->second.parent_path(),
                                                    m_file_path.parent_path()).generic_string() /
                               path->second.filename());
        } else{
            content_new.append(link);
        }

        //move to find next
        pos = iter_link_end - m_content.begin();
        iter_copy_start = iter_link_end;
    }

    //copy rest
    content_new.append(string(iter_copy_start, m_content.end()));

    swap(m_content, content_new);

}

void CFileCss::notch(CStats & stats){
    ++stats.css_files;
}
