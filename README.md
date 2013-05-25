pdffoldersearch
===============

About 1.5 years ago I quickly hacked a little tool together that allows to search 
folders containing PDF documents for search terms in those PDFs.

It is currently being used to search a manual all at once that comprises multiple PDF documents.

There are quite some TODOs left since it was a really quick hack and not everything is optimal but it is usuable.
Feel free to clone it and use it and adapt it for whatever purposes you want. 
If you do, a little message is of course always appreciated.


Some instructions on getting it set up:
    
    You need all the qt4 dev as well as libpoppler-dev.
    In ubuntu, looking in the packetmanager for qt4 dev should be quite easy 
    and for libpoppler you need the packages: libpoppler-qt4 and libpoppler-qt4-dev
    
    After installing those dependencies you should be able to simply open the .pro file
    in QT creator and compile the program
    
    
To run it:
    You can specify up to 3 arguments via command line.
    
    1. (obligatory) The path to the folder containing the PDFs
    2. (voluntary) The path to a copy of Adobe Reader
    3. (voluntary) The maximal number of possible hits (in order to prevent searches that take forever)
    
Here are binaries for windows and linux:

Windows:
Please get the binary [here][1]

Just extract the zip file. I provided a sample *.bat file for how to run the application.
Simply adjust the *.bat file to your computer and execute it.
    
Linux:
Please get the binary [here][2]

You need to have libpoppler-qt4 and qt4 installed on your system. I have compiled this
binary on Kubuntu 13.04.
    
[1]: http://anonoia.org/owncloud/public.php?service=files&t=0855a37fa0abd076a5e910e444fc46f4
[2]: http://anonoia.org/owncloud/public.php?service=files&t=bc91ab1211fb122fe4c6cc7771e14bd3

AND here is the corresponding blog entry:
http://myvirtualbrain.blogspot.de/2013/05/a-pdf-search-tool.html
    
Enjoy!
