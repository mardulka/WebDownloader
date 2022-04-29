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

    //Using size_t pos instead of iterators.
    //Iterators may become invalid after replace some part of content.

    for (size_t pos1 = 0 ; pos1 < m_content.size() ; ++pos1){
        //check if tag starts
        if (m_content[pos1] != '<' || m_content[pos1 + 1] == '/')
            continue;

        auto pos2 = ++pos1;
        for (; m_content[pos2] != ' ' ; ++pos2){}
        string tag_name = m_content.substr(pos1, pos2 - pos1);

        //find ending '>' tag
        auto pos3 = pos1;
        while (pos3 != '>')
            ++pos3;

        //find link in tags as position limits <a, b)
        optional<pair<size_t, size_t >> link_limits = nullopt;
        if (tag_name == "a"){
            link_limits = findLinkA(pos1, pos3);
        } else if (tag_name == "img"){
            link_limits = findLinkSrc(pos1, pos3);
        } else if (tag_name == "link"){
            link_limits = findLinkCss(pos1, pos3);
        } else if (tag_name == "script"){
            link_limits = findLinkSrc(pos1, pos3);
        }

        //make absolute + replace + add to links
        if (!link_limits.has_value())
            continue;
        auto absolute_link = makeLinkAbsolute(string(m_content, link_limits->first, link_limits->second));
        if (!absolute_link.has_value())
            continue;
        m_content.replace(link_limits->first, link_limits->second - link_limits->first, absolute_link.value());

        //insert into list for further return
        links.emplace_back(absolute_link.value());

    }

    return links;
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkA(const size_t & start, const size_t & end){
    auto pos1 = start;

    size_t link_start;
    size_t link_end;

    while (pos1 < end){
        //skip first space
        if (pos1 == ' ' && pos1 < end)
            ++pos1;

        //read one attribute
        auto pos2 = pos1; //pos2 = attr_end
        while (pos2 < end && m_content[pos1] != ' ')
            ++pos2;

        //read tag
        auto pos3 = pos1; //pos3 = tag_end
        string attribute(m_content, pos1, pos3);
        while (m_content[pos3] != '=' || pos3 < pos2){
            attribute.append(1, m_content[pos1]);
        }

        //check if is href, if not, skip attribute and go to next tag
        if (attribute != "href"){
            pos1 = pos2;
            continue;
        }


        //move pos3 behind '"' with check
        if ((pos3 + 2) < pos2)
            link_start = pos3 + 2;
        else
            break;

        //find ending '"'
        link_end = link_start;
        while (m_content[link_end] != '"' || link_end < pos2){
            ++link_end;
        }

        //return limits
        return make_pair(link_start, link_end);
    }

    //no href found, therefore empty optional returned
    return {};
}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkSrc(const size_t & start, const size_t & end){
    auto pos1 = start;

    size_t link_start;
    size_t link_end;

    while (pos1 < end){
        //skip first space
        if (pos1 == ' ' && pos1 < end)
            ++pos1;

        //read one attribute
        auto pos2 = pos1; //pos2 = attr_end
        while (pos2 < end && m_content[pos1] != ' ')
            ++pos2;

        //read tag
        auto pos3 = pos1; //pos3 = tag_end
        string attribute(m_content, pos1, pos3);
        while (m_content[pos3] != '=' || pos3 < pos2){
            attribute.append(1, m_content[pos1]);
        }

        //check if is src, if not, skip attribute and go to next tag
        if (attribute != "src"){
            pos1 = pos2;
            continue;
        }


        //move pos3 behind '"' with check
        if (pos3 + 2 < pos2)
            link_start = pos3 + 2;
        else
            break;

        //find ending '"'
        link_end = link_start;
        while (m_content[link_end] != '"' || link_end < pos2){
            ++link_end;
        }

        //return limits
        return make_pair(link_start, link_end);
    }

    //no src found, therefore empty optional returned
    return {};

}

std::optional<std::pair<size_t, size_t>> CFileHtml::findLinkCss(const size_t & start, const size_t & end){
    auto pos1 = start;

    size_t link_start = 0;
    size_t link_end = 0;

    bool rel = false;
    bool href = false;

    while (pos1 < end){
        //skip first space
        if (pos1 == ' ' && pos1 < end)
            ++pos1;

        //read one attribute
        auto pos2 = pos1; //pos2 = attr_end
        while (pos2 < end && m_content[pos1] != ' ')
            ++pos2;

        //read tag
        auto pos3 = pos1; //pos3 = tag_end
        string attribute(m_content, pos1, pos3);
        while (m_content[pos3] != '=' || pos3 < pos2){
            attribute.append(1, m_content[pos1]);
        }

        //check if is href, if not, skip attribute and go to next tag
        if (attribute == "href"){
            //move pos3 behind '"' with check
            if ((pos3 + 2) < pos2)
                link_start = pos3 + 2;
            else
                break;

            //find ending '"'
            link_end = link_start;
            while (m_content[link_end] != '"' || link_end < pos2){
                ++link_end;
            }

            //if rel done, loop can end
            href = true;
            if (rel)
                break;

        } else if (attribute == "rel"){
            //move pos3 behind '"' with check
            if ((pos3 + 2) < pos2)
                pos3 += 2;
            else
                break;

            //find ending '"'
            auto pos4 = pos3;
            while (m_content[pos4] != '"' || pos4 < pos2){
                ++pos4;
            }
            //if rel is stylesheet, can go to next tag
            if (string(m_content, pos3, pos4) == "stylesheet")
                rel = true;

            //if href done, loop can end
            if (href)
                break;

        } else{
            pos1 = pos2;
            continue;
        }
    }

    //no href found or no rel therefore empty optional returned
    if (!rel || (link_start == 0 && link_end == 0))
        return {};
    else
        return make_pair(link_start, link_end);

}