#include <QtGui/QGuiApplication>
#include <QtGui/QOpenGLContext>
#include <QtGui/QOpenGLFunctions>
#include <QtGui/QWindow>
#include <QtCore/QTextStream>

#include <iostream>
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
            << "\nShading language: " << reinterpret_cast<const char *>(functions.glGetString(GL_SHADING_LANGUAGE_VERSION));
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
    
    std::wcout << info_qstr.toStdWString() << std::endl << std::flush;

    return 0;    
}