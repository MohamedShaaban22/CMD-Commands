# CMD-Commands
p_name      :: take path and return dirictory path (path e:\asd\file)__>return e:\asd ;
p_name      :: take path and return file name (path e:\asd\file)__>return file ;
file_or_dir :: take path and return (1 if path is dir || 2 if path is file || 0 if either dor nor file ); 
change_path :: take file path and return path with path that are stand in if it's have not (like path = asd __> return c:\asd) ;
path        :: chang path dirictly like ( e: ) and make it global path  ;
split       :: take string and split it based in command ind pathes and return array of string  ;
dir         :: list dir's and files in dirictory ;
remove      :: take path of file and delete this file and boolian that determind if deletion this file in subdirictory or just in this path only 
remove_dir  :: take path of dir and delete this dir and boolian that determind if deletion tree of this dir or delet dir if is empty ;
cd          :: change path can work with .. mave bake one \ taht bake to current partion and with path to move too ;
find        :: take string and file path and search in this file for this string and print line that contain this string ;
type        :: take path and print it ;
help        :: print list of command use ;
copy        :: take path of file or dir and copy it in second path ;
xcopy       :: take path of dir and copy it in second path with tree of sub dir's ;
copmare     :: take two paths and print line different between them or number of line different ;
sort        :: take file path and sort content of it ;
main -------------------------------------------------------------------------------------------------------------------------------

take from user like >>   command ,  option , paths

check for command if found do it 

dir  call dir function ;
cls :: clear screen ;
del , erase :: check for options and call remove function ;
mkdir  :: check for folder if exist and make folder ;
cd :: chang current path by send path , .. , \
ren , rename :: check for name of file and rename name of file 
find :: look for string in file ,, can search in more one file 
rmdir :: check if folder exist and options to remove it use remove_dir function
mv , move :: move file , check if this file not in path that will move to
type :: print content of file on screen
help :: print use of command 
xcopy :: like copy but her is option that copy tree of this folder use xcopy function
comp ::  copare filees and print line deffrent , there is an option that print number of line 
sort :: sort file based on alphabitic line sort
