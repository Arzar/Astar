#ifndef _PATH_MANIPULER_H_
#define _PATH_MANIPULER_H_

class PathManipuler
{
	
	fs::path root_path;
	
public:
	PathManipuler():root_path(fs::current_path())
	{
	}

	PathManipuler(const fs::path& root_path):root_path(root_path)
	{
	}

	std::vector<fs::path> FindDirectories(const std::string& dir_name) const;
	fs::path FindDirectory(const std::string& dir_name) const;
	std::vector<fs::path> FindFiles(const fs::path& search_path, const std::string& extension) const;
	
};



#endif 

