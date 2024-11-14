cmake_minimum_required(VERSION 3.16)

project(InLanD_Compiler VERSION 0.1 LANGUAGES CXX)

# Habilitar las funciones automáticas de CMake para Qt
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

# Establecer el estándar de C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Encontrar Qt y sus componentes requeridos
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets LinguistTools)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets LinguistTools)

# Definir los archivos de traducción
set(TS_FILES InLanD_Compiler_es_MX.ts)

# Consolidar todas las fuentes del proyecto en una sola variable
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    analyzer.cpp
    mainwindow.h
    analyzer.h
    token.h
    mainwindow.ui
    ${TS_FILES}
)

# Agregar el ejecutable usando qt_add_executable (Qt6) o add_executable (Qt5)
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(InLanD_Compiler
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
    # Define propiedades para Android con Qt 6 si es necesario
    # set_property(TARGET InLanD_Compiler APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #              ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # Más información: https://doc.qt.io/qt-6/qt-add-executable.html#target-creation

    # Crear los archivos de traducción
    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(InLanD_Compiler SHARED
            ${PROJECT_SOURCES}
        )
        # Define propiedades para Android con Qt 5 si es necesario
        # set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(InLanD_Compiler
            ${PROJECT_SOURCES}
        )
    endif()

    # Crear los archivos de traducción para Qt5
    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

# Enlazar las bibliotecas necesarias
target_link_libraries(InLanD_Compiler PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Configuración específica para iOS/macOS
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.InLanD_Compiler)
endif()
set_target_properties(InLanD_Compiler PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

# Incluir directorios de instalación estándar
include(GNUInstallDirs)

# Definir reglas de instalación
install(TARGETS InLanD_Compiler
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# Finalizar la configuración del ejecutable para Qt6
if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(InLanD_Compiler)
endif()
