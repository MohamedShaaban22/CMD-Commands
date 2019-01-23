#undef UNICODE
#define _SCL_SECURE_NO_WARNINGS
#include <windows.h>
#include <vector>
#include <algorithm>
#include <tchar.h> 
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <strsafe.h>
#include <iomanip>
#pragma comment(lib, "User32.lib")
using namespace std;
string gpath = "c:\\";
string p_name(string str)
{
	string s = "";
	while (str[str.length() - 1] != '\\')
	{
		s += str[str.length() - 1];
		str.erase(str.end() - 1, str.end());
	}
	str.erase(str.end() - 1, str.end());
	return str;
}
string f_name(string str)
{
	string s = "", ss = "";
	while (str[str.length() - 1] != '\\')
	{
		s += str[str.length() - 1];
		str.erase(str.end() - 1, str.end());
	}
	while (!s.empty())
	{
		ss += s[s.length() - 1];
		s.erase(s.end() - 1, s.end());
	}
	return ss;
}
int file_or_dir(string str)
{
	string s = p_name(str);
	string ss = f_name(str);
	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	hFind = FindFirstFile((s + "\\*").c_str(), &ffd);

	do
	{
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY&&ffd.cFileName == ss)
		{
			return 1;
		}
		else if (ffd.cFileName == ss)
		{
			return 2;
		}
	} while (FindNextFile(hFind, &ffd) != 0);
	FindClose(hFind);
	return 0;
}
void chang_path(string &s)
{
	s.c_str();
	if (!s.empty()&&s[1] != ':'&&gpath.length()>3)
		s = gpath + "\\"+s;
	else if(!s.empty() && s[1] != ':')
		s = gpath + s;
}
void path(string path)
{
	if (path == "")
		return;
	WIN32_FIND_DATA fd;
	HANDLE hFind = FindFirstFile((path + "\\*").c_str(), &fd);

	if (INVALID_HANDLE_VALUE == hFind)
		;
	else if (path.length() == 2)
		gpath = path + "\\";
	else
		gpath = path;
}
string* Split(string str,string arr_str[])
{
	string s = "";
	int count = 0;
	for (int i = 0;i < str.length();i++)
	{
		if (str[i] != ' '&& str[i] != '"')
		{
			s += str[i];
		}
		else if (str[i] == ' ')
		{
			arr_str[count] = s;
			count++;
			s = "";
		}
		else if (str[i] == '"')
		{
			i++;
			for (i;i < str.length();i++)
			{
				if (str[i] != '"')
				{
					s += str[i];
				}
				else if (str[i] == '"')
				{
					arr_str[count] = s;
					count++;
					s = "";
					break;
					i++;
				}
			}
			arr_str[count] = s;
			count++;
			s = "";
		}
		
	}
	arr_str[count] = s;
	count++;
	s = "";
	return arr_str;
}
int dir(string p)        //All folders at the specific path
{
	string path = p;
	WIN32_FIND_DATA ffd;
	LARGE_INTEGER filesize;

	size_t length_of_arg;
	HANDLE hFind = INVALID_HANDLE_VALUE;
	DWORD dwError = 0;

	length_of_arg = path.length();
	if (length_of_arg > (MAX_PATH - 3))
	{
		printf("\nDirectory path is too long.\n");
		return (-1);
	}

	cout << "\nDirectory of " << path << "\n\n";

	hFind = FindFirstFile((path + "\\*").c_str(), &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		cout << "FindFirstFile";
		return dwError;
	}
	do
	{
		FILETIME ff;
		FILETIME ftLocal;
		SYSTEMTIME stCreate;
		ff.dwHighDateTime = ffd.ftLastWriteTime.dwHighDateTime;
		ff.dwLowDateTime = ffd.ftLastWriteTime.dwLowDateTime;
		FileTimeToLocalFileTime(&ff, &ftLocal);
		FileTimeToSystemTime(&ftLocal, &stCreate);
		filesize.LowPart = ffd.nFileSizeLow;
		filesize.HighPart = ffd.nFileSizeHigh;
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			printf(TEXT(" %02d/%02d/%d %02d:%02d:%02d <DIR>	           %s \n"), stCreate.wMonth, stCreate.wDay, stCreate.wYear,stCreate.wHour, stCreate.wMinute, stCreate.wSecond, ffd.cFileName);
		}
		else
		{

			filesize.LowPart = ffd.nFileSizeLow;
			filesize.HighPart = ffd.nFileSizeHigh;
			printf(TEXT(" %02d/%02d/%d %02d:%02d:%02d	        %ld bytes  "), stCreate.wMonth, stCreate.wDay, stCreate.wYear, stCreate.wHour, stCreate.wMinute, stCreate.wSecond, filesize.QuadPart); cout << "  " << ffd.cFileName << endl;
		}
	} while (FindNextFile(hFind, &ffd) != 0);

	dwError = GetLastError();
	if (dwError != ERROR_NO_MORE_FILES)
	{
		cout << "FindFirstFile";
	}

	FindClose(hFind);
	return dwError;
	system("pause");
}
void remove(string str , bool b)
{
	chang_path(str);
	
	if (b)
	{
		string s = p_name(str), ss = f_name(str), sss = "";
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		hFind = FindFirstFile((s + "\\*").c_str(), &ffd);

		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY&&ffd.cFileName[0] != '.')
			{
				string new_path = s + "\\" + ffd.cFileName+"\\"+ss;
				remove(new_path.c_str(), true);
			}
			else if (ffd.cFileName == ss)
			{
				sss = s + "\\" + ss;
				if (remove(sss.c_str()) != 0)
					cout << "Could Not Find " << sss << endl;
			}

		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}
	else
		if (remove(str.c_str()) != 0)
			cout << "Could Not Find or not a file"<<str<<endl;
}
void remove_dir(string str,bool b)
{
	chang_path(str);
	if (b)
	{
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		hFind = FindFirstFile((str + "\\*").c_str(), &ffd);
		RemoveDirectory(str.c_str());
		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY&&ffd.cFileName[0] != '.')
			{
				string new_path = str + "\\" + ffd.cFileName;
				remove_dir(new_path.c_str(), true);
			}
			else if (ffd.cFileName[0] != '.')
			{
				string new_path = str + "\\" + ffd.cFileName;
				if (remove(new_path.c_str()) != 0)
					cout << "Could Not Find " << str << endl;
			}
			else
				RemoveDirectory(str.c_str());

		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
		RemoveDirectory(str.c_str());
	}
	else if (file_or_dir(str) == 1)
		if (RemoveDirectory(str.c_str()) != -1)
			cout << "this file not empty.\n";

}
void cd(string s)
{
	if (s == "..")
	{
		while (gpath[gpath.length() - 1] != '\\')
		{
			gpath.erase(gpath.end() - 1, gpath.end());
		}
		if (gpath.length()>3)
			gpath.erase(gpath.end() - 1, gpath.end());
	}
	else if (s == "\\")
	{
		gpath = gpath[0];
		gpath += ":\\";
	}
	else if(s.length()>1)
	{
		chang_path(s);
		path(s);
	}
}
void find(string key, string path)
{
	chang_path(path);
	if (file_or_dir(path) == 2)
	{
		int i = 0;
		fstream file(path, ios::in | ios::out);
		string line;
		cout << "\n---------- " << path << " \n";
		while (getline(file, line))
		{
			if (line.find(key) != -1)
			{
				i++;
				cout << line << endl;
			}
		}
		cout << "\n";
	}
	else
		cout << "File not found - "<<path<<"  \n\n";
	
	


}
void type(string path)
{
	if (file_or_dir(path) == 2)
	{
		fstream file(path, ios::in | ios::out);
		string line;
		while (getline(file, line))
		{
			cout << line << endl;
		}
	}
	else
		cout << "there is an error with file name\n";
	



}
void help()
{
	cout << "CD             Displays the name of or changes the current directory.\n"
		<< "CLS            Clears the screen.\n"
		<< "COMP           Compares the contents of two files or sets of files.\n"
		<< "COPY           Copies one or more files to another location.\n"
		<< "DATE           Displays or sets the date.\n"
		<< "DEL            Deletes one or more files.\n"
		<< "ERASE          Deletes one or more files.\n"
		<< "EXIT           Quits the CMD.EXE program (command interpreter).\n"
		<< "FIND           Searches for a text string in a file or files.\n"
		<< "HELP           Provides Help information for Windows commands.\n"
		<< "MD             Creates a directory.\n"
		<< "MKDIR          Creates a directory.\n"
		<< "MOVE           Moves one or more files from one directory to anotherdirectory.\n"
		<< "PRINT          Prints a text file.\n"
		<< "RD             Removes a directory.\n"
		<< "REN            Renames a file or files.\n"
		<< "RENAME         Renames a file or files.\n"
		<< "RMDIR          Removes a directory.\n"
		<< "TIME           Displays or sets the system time.\n"
		<< "TYPE           Displays the contents of a text file.\n"
		<< "XCOPY          Copies files and directory trees.\n";
}
void copy(string origin_path, string path)
{
	if (file_or_dir(origin_path) == 1)
	{
		string f_path = "", t_path = "";
		string dir_p = path + "\\" + f_name(origin_path);
		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		hFind = FindFirstFile((origin_path + "\\*").c_str(), &ffd);

		CreateDirectory(dir_p.c_str(), NULL);
		do
		{
				t_path = dir_p + "\\" + ffd.cFileName;
				f_path = origin_path + "\\" + ffd.cFileName;
				CopyFile(f_path.c_str(), t_path.c_str(), FALSE);

		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}
	else if (file_or_dir(origin_path) == 2)
	{
		string ss = f_name(origin_path);
		path += "\\" + ss;
		CopyFile(origin_path.c_str(), path.c_str(), FALSE);
	}
	else
		cout<<"there an error with file name\n";
	
	
}
void xcopy(string origin_path, string path)
{
	if (file_or_dir(origin_path) == 1)
	{
		string f_path = "", t_path = "", dir_p = path + "\\" + f_name(origin_path);

		WIN32_FIND_DATA ffd;
		HANDLE hFind = INVALID_HANDLE_VALUE;
		hFind = FindFirstFile((origin_path + "\\*").c_str(), &ffd);

		CreateDirectory(dir_p.c_str(), NULL);

		do
		{
			if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY&&ffd.cFileName[0] != '.')
			{
				string s = origin_path + "\\" + ffd.cFileName;
				xcopy(s, dir_p.c_str());
			}
			else
			{
				t_path = dir_p + "\\" + ffd.cFileName;
				f_path = origin_path + "\\" + ffd.cFileName;
				CopyFile(f_path.c_str(), t_path.c_str(), FALSE);
			}


		} while (FindNextFile(hFind, &ffd) != 0);
		FindClose(hFind);
	}
	else
		cout << "there an error with file name\n";
}
void compare(string file1, string file2, int x)
{
	chang_path(file1);
	chang_path(file2);
	if (x == 1)
	{
		if (file_or_dir(file1) == 2 && file_or_dir(file2) == 2)
		{
			int count = 1, def = 0;
			fstream file_1(file1, ios::in | ios::out);
			fstream file_2(file2, ios::in | ios::out);
			string line_1,line_2;
			while (getline(file_1, line_1)&& getline(file_2, line_2))
			{
				if (line_1.compare(line_2) == 0)
					count++;
				else
				{
					cout << count << endl;
					count++; def++;
				}
			}
			while (getline(file_2, line_2))
			{
				cout << count << endl;
				count++; def++;
			}
			while (getline(file_1, line_1))
			{
				cout << count << endl;
				count++; def++;
			}
			file_1.close(); file_2.close();
			cout << "there is an "<<def<<" lines diffrent betwwen files \n";
		}
		else
			cout << "there is an error with files names\n";
	}
	else if (x == 2)
	{
		if (file_or_dir(file1) == 2 && file_or_dir(file2) == 2)
		{
			int count = 1, def = 0;
			fstream file_1(file1, ios::in | ios::out);
			fstream file_2(file2, ios::in | ios::out);
			string line_1, line_2;
			while (getline(file_1, line_1) && getline(file_2, line_2))
			{
				if (line_1.compare(line_2) == 0)
					count++;
				else
				{
					cout << count <<"  : "<<line_1<< endl;
					cout << count << "  : " << line_2 << endl;
					count++; def++;
				}
			}
			while (getline(file_2, line_2))
			{
				cout << count << "  : " << endl;
				cout << count << "  : " << line_2 << endl;
				count++; def++;
			}
			while (getline(file_1, line_1))
			{
				cout << count << "  : " << line_1 << endl;
				cout << count << "  : " << endl;
				count++; def++;
			}
			file_1.close(); file_2.close();
			cout << "there is an " << def << " lines diffrent betwwen files \n";
		}
		else
			cout << "there is an error with files names\n";

	}
	else
	{
		cout << "there is an error with use of comp command\n";
	}

}
void sort(string file)
{
	chang_path(file);
	if (file_or_dir(file) == 2)
	{
		fstream file_1(file, ios::in | ios::out);
		string line_1;
		int i=0;
		vector<string> vec;
		while (getline(file_1, line_1))
		{
			vec.push_back(line_1);
		}
		file_1.close();
		sort(vec.begin(),vec.end());
		fstream file1(file, ios::in | ios::out|ios::trunc);
		for(int x=0;x<vec.size();x++)
		{
			line_1 = vec[i];
			i++;
			file1 << line_1 << endl;
		}
		file1.close();

	}
	else
	{
		cout << "there is an error with file name\n";
	}
}

void main()
{ 
	do
	{
		string s;
		cout << gpath + ">";
		getline(cin, s);
		path(s);
		string command_paths[10];
		Split(s,command_paths);
		for (int f = 0; f < command_paths[0].length(); f++)
		{
			if (command_paths[0][f] < 'a')
				command_paths[0][f] += 32;
		}

		if (command_paths[0] == "dir")
		{
			string path;
			if (command_paths[1] != "")
			{
				chang_path(command_paths[1]);
				path = command_paths[1];
			}
				 
			else
				path = gpath;
			dir(path);

		}

		else if (s == "cls")
		{
			system("cls");
		}

		else if (s == "exit")
		{
			exit(0);
		}

		else if (command_paths[0] == "copy")
		{
			chang_path(command_paths[1]);
			copy(command_paths[1], command_paths[2]);
		}

		else if (command_paths[0] == "del" || command_paths[0] == "erase")
		{
			if (command_paths[1] == "/s")
				remove(command_paths[2],true);
			else
				remove(command_paths[1],false);
		}

		else if (command_paths[0] == "mkdir")
		{
			chang_path(command_paths[1]);
			if (file_or_dir(command_paths[1]) == 1)
			{
				cout << "A subdirectory or file "<< command_paths[1]<<" already exists.\n";
			}
			else
				CreateDirectory(command_paths[1].c_str(), NULL);
		}

		else if (command_paths[0] == "cd")
		{
			cd(command_paths[1].c_str());
		}

		else if (command_paths[0]=="ren"|| command_paths[0] == "rename")
		{
			chang_path(command_paths[1]);
			chang_path(command_paths[2]);
			if (file_or_dir(command_paths[2]) == 2)
			{
				cout << "A duplicate file name exists, or the file\ncannot be found.\n";
			}
			else
				rename(command_paths[1].c_str(), command_paths[2].c_str());
		}

		else if (command_paths[0] == "find")
		{
			int i = 2;
			asd : 
				if (command_paths[i] != "")
				{
					i++;
					goto asd;
				}
			for (int o =2;o<i;o++)
				find(command_paths[1].c_str(), command_paths[o].c_str());
		}

		else if (command_paths[0] == "rmdir")
		{
			if (command_paths[1] == "/s")
				if(command_paths[2] == "/q")
					remove_dir(command_paths[3], true);
				else
				{
					chang_path(command_paths[3]);
					if (file_or_dir(command_paths[2]) == 1)
					{
						string c;
					qwe: cout << command_paths[2] << ", Are you sure (Y/N)? ";
						getline(cin, c);
						if (c == "y")
						{
							remove_dir(command_paths[2], true);
						}
						else if (c == "n")
							;
						else
							goto qwe;
					}
					else
						cout << "The system cannot find the file specified.\n";
				}
			else
				remove_dir(command_paths[1],false);
		}

		else if (command_paths[0] == "mv"|| command_paths[0] == "move")
		{
			chang_path(command_paths[1]);
			chang_path(command_paths[2]);
			if (file_or_dir(command_paths[1]) == 2)
			{
				MoveFile(command_paths[1].c_str(), command_paths[2].c_str());
				if (f_name(command_paths[1]) != f_name(command_paths[2]))
				{
					command_paths[2] += "\\" + f_name((command_paths[1]));
					MoveFile(command_paths[1].c_str(), command_paths[2].c_str());
				}
			}
		}

		else if (command_paths[0] == "type")
		{
			chang_path(command_paths[1]);
			type(command_paths[1].c_str());
		}

		else if (command_paths[0] == "help")
		{
			help();
		}

		else if (command_paths[0] == "xcopy")
		{
			if(command_paths[1] == "/e")
			{
				chang_path(command_paths[2]);
				xcopy(command_paths[2], command_paths[3]);
			}
			else
			{
				chang_path(command_paths[2]);
				copy(command_paths[1].c_str(), command_paths[2].c_str());
			}
				
		}

		else if (command_paths[0] == "comp")
		{
			if (command_paths[1] == "/l")
				compare(command_paths[2], command_paths[3], 1);
			else
				compare(command_paths[1], command_paths[2], 2);
		}
		else if (command_paths[0] == "sort")
		{
			sort(command_paths[1]);
		}
		

	} while (true);

}





