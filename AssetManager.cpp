extern "C" {
#include "utils.h"
}
#include "AssetManager.h"


void AssetManager::loadFileFromResource(QString& s) {
    QResource::registerResource(s);
//    QResource res("myresources.rcc");
//    res.registerResource("myresources.rcc");
    Q_INIT_RESOURCE(application);
#ifdef __gnu_linux__
    LOG_setNorm("/home/QT5/MathForFun/Logs/logfile_norm");
    LOG_setErr("/home/QT5/MathForFun/Logs/logfile_err");
    LOG_setOther("/home/QT5/MathForFun/Logs/logfile_other");
#endif

}
