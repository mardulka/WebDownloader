#include "CSettings.h"

bool CSettings::pictures = false;
bool CSettings::scripts = false;
bool CSettings::errorPage = false;
int CSettings::levels = -1;
std::filesystem::path CSettings::targetFolder = std::filesystem::path();
CUrl CSettings::url = CUrl();
