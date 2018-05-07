#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QWindow>
#include <QtCore/QTextStream>

#include <iostream>
#include <fstream>
#include <string>


void dumpGlInfo(QTextStream &str)
{
    QOpenGLContext context;
    if (context.create())
    {
        switch (context.openGLModuleType())
        {
        case QOpenGLContext::LibGL:
            str << "LibGL";
            break;
        case QOpenGLContext::LibGLES:
            str << "LibGLES";
            break;
        }
        QWindow window;
        window.setSurfaceType(QSurface::OpenGLSurface);
        window.create();
        context.makeCurrent(&window);
        QOpenGLFunctions functions(&context);
        str << " Vendor: " << reinterpret_cast<const char *>(functions.glGetString(GL_VENDOR))
            << "\nRenderer: " << reinterpret_cast<const char *>(functions.glGetString(GL_RENDERER))
            << "\nVersion: " << reinterpret_cast<const char *>(functions.glGetString(GL_VERSION))
            << "\nShading Language: " << reinterpret_cast<const char *>(functions.glGetString(GL_SHADING_LANGUAGE_VERSION));
    }
    else
    {
        str << "ERROR: Unable to create an Open GL context.\n";
    }
}

QString qtDiag()
{
    QString result;
    QTextStream str(&result);
    dumpGlInfo(str);
    return result;
}

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);
    QString info_qstr = qtDiag();

    if (argc == 2 && std::string(argv[1]) == "-h")
    {
        std::cout << "Usage: glinfo [-f filename]" << std::endl;
        return 0;
    }

    std::wcout << info_qstr.toStdWString() << std::flush;

    if (argc == 3 && std::string(argv[1]) == "-f")
    {
        std::ofstream file(argv[2]);
        file << info_qstr.toStdString() << std::flush;
    }

    return 0;
}