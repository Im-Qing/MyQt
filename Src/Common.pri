QMAKE_CXXFLAGS += /utf-8
CONFIG(debug,debug|release){
    TARGET = $${TARGET}d
}
CONFIG(release,debug|release){

}
