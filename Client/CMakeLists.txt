cmake_minimum_required(VERSION 3.30)

project(Echoo-Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON) # Globally preventing the fallback behaviour of C++ standard

find_package(Qt6 REQUIRED COMPONENTS Quick Network)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appEchoo-Client)

qt_add_qml_module(appEchoo-Client
    URI Echoo-Client
    VERSION 1.0
    QML_FILES
    StartWindow.qml LoginForm.qml TitleBar.qml RegForm.qml ToolBars.qml
    SOURCES
        main.cpp echooclient.h echooclient.cpp
    RESOURCES
        Img.qrc
        QML_FILES ChatWidget.qml
        QML_FILES TopBar.qml
        QML_FILES MainpagetitleBar.qml
        QML_FILES FrameLessWindow.qml
        QML_FILES Messagetotal.qml
        QML_FILES MessageItem.qml
        QML_FILES EmojiPopup.qml
        QML_FILES PersonPage.qml
        QML_FILES FriendItem.qml
        QML_FILES Friendtotal.qml
        QML_FILES Friendlist.qml
        QML_FILES Friends.qml
        QML_FILES EditTitle.qml
        QML_FILES EditProfile.qml
        QML_FILES Maintotal.qml
        QML_FILES GroupItem.qml
        QML_FILES Grouptotal.qml
        QML_FILES GroupChat.qml
        QML_FILES Groupnotification.qml
        QML_FILES Friendnotification.qml
        QML_FILES SelectFriends.qml
        QML_FILES SelectTitleBar.qml
)

target_compile_features(appEchoo-Client PRIVATE cxx_std_23)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appEchoo-Client PROPERTIES
    AUTORCC TRUE
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEchoo-Client
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appEchoo-Client
    PRIVATE
        Qt6::Quick
        Qt6::Network
)

include(GNUInstallDirs)
install(TARGETS appEchoo-Client
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)




























































#qt_add_executable(Echoo-Client)  //Creates and finalizes an application target of a platform-specific type.
#This command performs the following tasks:
#    1. Create a CMake target of the appropriate type for the target platform.
#    2. Link the target to the Qt::Core library.
#    3. Handle finalization of the CMake target.



# qt_standard_project_setup()     #set(CMAKE_AUTOUIC ON)  set(CMAKE_AUTOMOC ON)

# @if %{HasTranslation}
# find_package(Qt6 REQUIRED COMPONENTS Core Quick LinguistTools)
# @else
# find_package(Qt6 REQUIRED COMPONENTS Core Quick)
# @endif

# target_sources(appEchoo-Client
#     PRIVATE
#         main.cpp
#         qml.qrc
#     @if %{HasTranslation}
#         %{TsFileName}
#     @endif
#
#     PUBLIC
#
# )

# qt_import_qml_plugins(Echoo-Client)

















# cmake_minimum_required(VERSION 3.16)
#
# project(Echoo-Client VERSION 0.1 LANGUAGES CXX)
#
# @if !true
# set(CMAKE_AUTOMOC ON)
# @endif
# set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
# find_package(Qt6 6.5 REQUIRED COMPONENTS Quick)
#
# @if true
# @if true
# qt_standard_project_setup(REQUIRES 6.5)
# @else
# qt_standard_project_setup()
# @endif
# @endif
#
# qt_add_executable(appEchoo-Client
#     main.cpp
# )
#
# qt_add_qml_module(appEchoo-Client
#     URI Echoo-Client
#     VERSION 1.0
#     QML_FILES Main.qml
# )
#
# # Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# # If you are developing for iOS or macOS you should consider setting an
# # explicit, fixed bundle identifier manually though.
# set_target_properties(appEchoo-Client PROPERTIES
# #    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEchoo-Client
#     MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
#     MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
#     MACOSX_BUNDLE TRUE
#     WIN32_EXECUTABLE TRUE
# )
#
# target_link_libraries(appEchoo-Client
#     PRIVATE Qt6::Quick
# )
#
# include(GNUInstallDirs)
# install(TARGETS appEchoo-Client
#     BUNDLE DESTINATION .
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
# )
