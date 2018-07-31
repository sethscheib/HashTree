# HashTree

Program compiled from terminal with -lssl -lcrypto dependencies
  gcc -o main main.c -lssl -lcrypto
  
Program accesses "files" directory creating a SHA1 hash code for all the files within the directory.

Testing was as such:
  list files directory
  show example content of files
  execute program - displays hash
  edit file
  execute program - displays new hash
  make a new random file (script included in repo)
  list all files
  execute program - displays new hash
  execute program - displays same hash
