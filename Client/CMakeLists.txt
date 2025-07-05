cmake_minimum_required(VERSION 3.30)

project(Echoo-Client VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON) # Globally preventing the fallback behaviour of C++ standard

find_package(Qt6 REQUIRED COMPONENTS Quick Network Sql)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appEchoo-Client)

qt_add_qml_module(appEchoo-Client
    URI Echoo-Client
    VERSION 1.0
    RESOURCES
        Img.qrc
        SOURCES CPP/communicator.cpp CPP/databasemanager.cpp CPP/echooclient.cpp CPP/group.cpp CPP/logger.cpp CPP/main.cpp CPP/message.cpp CPP/netizen.cpp
        SOURCES CPP_Header/communicator.h CPP_Header/databasemanager.h CPP_Header/echooclient.h CPP_Header/group.h CPP_Header/logger.h CPP_Header/message.h CPP_Header/netizen.h
        QML_FILES QML/Addfriend.qml QML/ChatWidget.qml QML/EditProfile.qml QML/EditTitle.qml QML/EmojiPopup.qml QML/FrameLessWindow.qml QML/FriendItem.qml QML/Friendlist.qml QML/Friendnotification.qml QML/Friendpersonpage.qml QML/Friends.qml QML/Friendtotal.qml QML/LoginForm.qml QML/MainpagetitleBar.qml QML/Maintotal.qml QML/MessageItem.qml QML/Messagetotal.qml QML/MessageWidget.qml QML/PersonPage.qml QML/RegForm.qml QML/StartWindow.qml QML/TitleBar.qml QML/ToolBars.qml QML/TopBar.qml
        QML_FILES listmodels.js
        SOURCES CPP_Header/udpbroadcaster.h CPP/udpbroadcaster.cpp
        SOURCES CPP_Header/tcpmanager.h CPP/tcpmanager.cpp
        SOURCES CPP_Header/messagesender.h CPP/messagesender.cpp
        SOURCES CPP_Header/messageprocessor.h CPP/messageprocessor.cpp
)

source_group("QML Files\\Account Window" FILES
    QML/LoginForm.qml
    QML/RegForm.qml
    QML/StartWindow.qml
)

source_group("QML Files\\Template" FILES
    QML/FrameLessWindow.qml
    QML/TitleBar.qml
)

source_group("QML Files\\MainWindow" FILES
    QML/Maintotal.qml
    QML/Friendtotal.qml
    QML/Messagetotal.qml
    QML/ToolBars.qml
    QML/MainpagetitleBar.qml
)

source_group("QML Files\\ChatWidget" FILES
    QML/ChatWidget.qml
    QML/MessageItem.qml
    QML/EmojiPopup.qml
    QML/MessageWidget.qml
    QML/TopBar.qml
)

source_group("QML Files\\FriendWidget" FILES
    QML/Friendlist.qml
    QML/Friends.qml
    QML/FriendItem.qml
    QML/Friendnotification.qml
    QML/Friendpersonpage.qml
    QML/Addfriend.qml
)

source_group("QML Files\\PersonPage" FILES
    QML/PersonPage.qml
    QML/EditProfile.qml
    QML/EditTitle.qml
    QML/Avatar.qml
)

target_include_directories(appEchoo-Client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/CPP_Header)

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
        Qt6::Sql
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
