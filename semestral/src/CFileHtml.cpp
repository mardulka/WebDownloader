#include "CFileHtml.h"

#include <utility>

using namespace std;

CFileHtml::CFileHtml(CUrl url, const string & relative_path)
        : CFile(std::move(url), relative_path, "html", CFileType::HTML){}

void CFileHtml::replaceLinks(){
    //TODO parse html to get links
    //TODO for every link replace from map with path (absolute / relative?)
}

list<CUrl> CFileHtml::readLinks(){
    list<CUrl> links;

    for (size_t pos1 = 0 ; pos1 < m_content.size() ; ++pos1){
        //check if tag starts
        if (m_content[pos1] != '<' || m_content[pos1 + 1] == '/')
            continue;

        auto pos2 = ++pos1;
        for (; m_content[pos2] != ' ' ; ++pos2){}
        string tag_name = m_content.substr(pos1, pos2 - pos1);

        //find ending '>' tag
        auto pos3 = pos1;
        while (m_content[pos3] != '>')
            ++pos3;

        //find link in tags as position limits <a, b)
        optional<pair<size_t, size_t >> link_limits = nullopt;
        if (tag_name == "a"){
            link_limits = findLinkA(pos2, pos3);
        } else if (tag_name == "img" || tag_name == "script"){
            link_limits = findLinkSrc(pos2, pos3);
        } else if (tag_name == "link"){
            link_limits = findLinkCss(pos2, pos3);
        } else{
            pos1 = pos3;
            continue;
        }

        //make absolute + add to links
        if (link_limits.has_value()){
            auto absolute_link = makeLinkAbsolute(
                    m_content.substr(link_limits->first, link_limits->second - link_limits->first));
            if (!absolute_link.has_value())
                continue;
            m_content.replace(link_limits->first, link_limits->second - link_limits->first, absolute_link.value());
            cout << "New tag: " << m_content << endl;

            //insert into list for further return
            links.emplace_back(absolute_link.value());
        }
        pos1 = pos3;
    }

    return links;
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkA(const size_t & start, const size_t & end){

    //TODO debug
    cout << "A-TAG: " << m_content.substr(start, end - start) << endl;

    auto attr_start = start;

    size_t link_start;
    size_t link_end;

    while (attr_start < end){
        //skip first spaces
        while (m_content[attr_start] == ' ' && attr_start < end)
            ++attr_start;

        //read attribute name
        auto attr_name_end = attr_start;
        while (m_content[attr_name_end] != '='){
            ++attr_name_end;
        }
        string attr_name = m_content.substr(attr_start, attr_name_end - attr_start);

        //check if attribute name is href, if not, skip attribute and go to next tag
        if (attr_name != "href"){
            attr_start = attr_name_end + 2;
            while (m_content[attr_start] != '"')
                ++attr_start;
            ++attr_start;
            continue;
        }

        cout << "Attribute HREF found" << endl; //TODO debug

        //move attr_name_end behind '"' with check
        link_start = attr_name_end + 2;

        //find ending '"'
        link_end = link_start;
        while (m_content[link_end] != '"'){
            ++link_end;
        }

        //return limits
        cout << "Link in HREF has indexes : [" << link_start << ", " << link_end << "]" << endl; //TODO debug
        return make_pair(link_start, link_end);
    }

    //no src found, therefore empty optional returned
    return {};
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkSrc(const size_t & start, const size_t & end){

    //TODO debug
    cout << "SRC-TAG: " << m_content.substr(start, end - start) << endl;

    auto attr_start = start;

    size_t link_start;
    size_t link_end;

    while (attr_start < end){
        //skip first spaces
        while (m_content[attr_start] == ' ' && attr_start < end)
            ++attr_start;

        //read attribute name
        auto attr_name_end = attr_start;
        while (m_content[attr_name_end] != '='){
            ++attr_name_end;
        }
        string attr_name = m_content.substr(attr_start, attr_name_end - attr_start);

        //check if attribute name is src, if not, skip attribute and go to next tag
        if (attr_name != "src"){
            attr_start = attr_name_end + 2;
            while (m_content[attr_start] != '"')
                ++attr_start;
            ++attr_start;
            continue;
        }

        cout << "Attribute SRC found" << endl; //TODO debug

        //move attr_name_end behind '"' with check
        link_start = attr_name_end + 2;

        //find ending '"'
        link_end = link_start;
        while (m_content[link_end] != '"'){
            ++link_end;
        }

        //return limits
        cout << "Link in SRC has indexes : [" << link_start << ", " << link_end << "]" << endl; //TODO debug
        return make_pair(link_start, link_end);
    }

    //no src found, therefore empty optional returned
    return {};

}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkCss(const size_t & start, const size_t & end){

    //TODO debug
    cout << "LINK-TAG: " << m_content.substr(start, end - start) << endl;

    auto attr_start = start;

    size_t link_start;
    size_t link_end;

    bool href = false;
    bool rel = false;

    while (attr_start < end || (!href && !rel)){
        //skip first spaces
        while (m_content[attr_start] == ' ' && attr_start < end)
            ++attr_start;

        //read attribute name
        auto attr_name_end = attr_start;
        while (m_content[attr_name_end] != '='){
            ++attr_name_end;
        }
        string attr_name = m_content.substr(attr_start, attr_name_end - attr_start);


        if (attr_name == "href"){
            cout << "Attribute HREF found" << endl; //TODO debug

            //move attr_name_end behind '"' with check
            link_start = attr_name_end + 2;

            //find ending '"'
            link_end = link_start;
            while (m_content[link_end] != '"'){
                ++link_end;
            }
            href = true;
        } else if (attr_name == "rel"){
            cout << "Attribute REL found" << endl; //TODO debug
            size_t rel_start = attr_name_end + 2;
            //find ending '"'
            size_t rel_end = rel_start;
            while (m_content[rel_end] != '"'){
                ++rel_end;
            }
            string rel_attr = m_content.substr(rel_start, rel_end - rel_start);
            if (rel_attr == "stylesheet"){
                rel = true;
                cout << "Attribute REL is STYLESHEET" << endl; //TODO debug
            }
        }

        //skip attribute
        attr_start = attr_name_end + 2;
        while (m_content[attr_start] != '"')
            ++attr_start;
        ++attr_start;

    }

    if (!href && !rel){
        //no src found, therefore empty optional returned
        return {};
    }

    //return limits
    cout << "Link in HREF has indexes : [" << link_start << ", " << link_end << "]" << endl; //TODO debug
    return make_pair(link_start, link_end);
}
