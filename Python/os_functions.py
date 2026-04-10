#file modification

#rename file
import os
'''
os.rename("test.txt","new.txt")
#os.rename(current_file_name, new_file_name): renames file
'''

#remove file
'''
os.remove("test.txt")
#os.remove(file_name):deletes file 
'''


#folder modification
#os.mkdir("New_folder")#os.mkdir:"newdir"  : creates new directory
os.chdir("/")#os.chdir("path")change directory , '/' to C:/
print(os.getcwd())#shows current directory
#os.rmdir('newname')
