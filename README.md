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
    
I will probably add some binaries for Windows and Linux here soon.