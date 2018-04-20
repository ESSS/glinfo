#include <QtGui/QGuiApplication>
#include <QtGui/QStyleHints>
#include <QtGui/QScreen>
#include <QtGui/QFont>
#include <QtGui/QFontDatabase>
#include <QtGui/QPalette>
#ifndef QT_NO_OPENGL
#  include <QtGui/QOpenGLContext>
#  include <QtGui/QOpenGLFunctions>
#  include <QtGui/QOpenGLVersionProfile>
#endif // QT_NO_OPENGL
#include <QtGui/QWindow>
#include <QtGui/QTouchDevice>
#ifdef NETWORK_DIAG
#  include <QSslSocket>
#endif
#include <QtCore/QLibraryInfo>
#include <QtCore/QStringList>
#include <QtCore/QVariant>
#include <QtCore/QSysInfo>
#include <QtCore/QLibraryInfo>
#include <QtCore/QTextStream>
#include <QtCore/QStandardPaths>
#include <QtCore/QDir>
#include <QtCore/QFileSelector>
#include <QtCore/QDebug>
#ifdef QT_WIDGETS_LIB
#  include <QtWidgets/QStyleFactory>
#endif
#include <algorithm>

#include <iostream>
#include <string>

bool with_flush = true;

QTextStream &operator<<(QTextStream &str, const QSurfaceFormat &format)
{
    str << "Version: " << format.majorVersion() << '.'
        << format.minorVersion() << " Profile: " << format.profile()
        << " Swap behavior: " << format.swapBehavior()
        << " Buffer size (RGB";
    if (format.hasAlpha())
        str << 'A';
    str << "): " << format.redBufferSize() << ',' << format.greenBufferSize()
        << ',' << format.blueBufferSize();
    if (format.hasAlpha())
        str << ',' << format.alphaBufferSize();
    if (const int dbs = format.depthBufferSize())
        str << " Depth buffer: " << dbs;
    if (const int sbs = format.stencilBufferSize())
        str << " Stencil buffer: " << sbs;
    const int samples = format.samples();
    if (samples > 0)
        str << " Samples: " << samples;
    return str;
}

void dumpGlInfo(QTextStream &str, bool listExtensions)
{
    QOpenGLContext context;
    if (context.create())
    {
#  ifdef QT_OPENGL_DYNAMIC
        str << "Dynamic GL ";
#  endif
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
            << "\nShading language: " << reinterpret_cast<const char *>(functions.glGetString(GL_SHADING_LANGUAGE_VERSION))
            << "\nFormat: " << context.format();
#  ifndef QT_OPENGL_ES_2
        GLint majorVersion;
        functions.glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
        GLint minorVersion;
        functions.glGetIntegerv(GL_MINOR_VERSION, &minorVersion);
        const QByteArray openGlVersionFunctionsName = "QOpenGLFunctions_"
            + QByteArray::number(majorVersion) + '_' + QByteArray::number(minorVersion);
        str << "\nProfile: None (" << openGlVersionFunctionsName << ')';
        if (majorVersion > 3 || (majorVersion == 3 && minorVersion >= 1))
        {
            QOpenGLVersionProfile profile;
            profile.setVersion(majorVersion, minorVersion);
            profile.setProfile(QSurfaceFormat::CoreProfile);
            if (QAbstractOpenGLFunctions *f = context.versionFunctions(profile))
            {
                if (f->initializeOpenGLFunctions())
                    str << ", Core (" << openGlVersionFunctionsName << "_Core)";
            }
            profile.setProfile(QSurfaceFormat::CompatibilityProfile);
            if (QAbstractOpenGLFunctions *f = context.versionFunctions(profile))
            {
                if (f->initializeOpenGLFunctions())
                    str << ", Compatibility (" << openGlVersionFunctionsName << "_Compatibility)";
            }
        }
        str << '\n';
#  endif // !QT_OPENGL_ES_2
    }
    else
    {
        str << "Unable to create an Open GL context.\n";
    }
}

QString qtDiag(unsigned flags)
{
    QString result;
    QTextStream str(&result);
    dumpGlInfo(str, flags);
    return result;
}

int main(int argc, char ** argv)
{
    QGuiApplication app(argc, argv);
    

    if (with_flush)
    {
        std::wcout << "WITH FLUSH AND EXTRA BLANK LINES" << std::endl;
    }
    else
    {
        std::wcout << "WITHOUT FLUSH" << std::endl;
    }
    
    std::wcout << qtDiag(0).toStdWString();

    if (with_flush)
    {
        std::wcout << std::endl;
        std::wcout.flush();

        for (int i = 0; i < 1000; i++)
        {
            std::wcout << "                                                                                " << std::endl;
        }
    }
    return 0;    
}