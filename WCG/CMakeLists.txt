# CMakeList.txt: CMake-Projekt für "WCG". Schließen Sie die Quelle ein, und definieren Sie
# projektspezifische Logik hier.
#

# Füge alle Header-Dateien im "inc"-Verzeichnis hinzu
file(GLOB HEADER_FILES "inc/*.h")

# Füge alle Quellcode-Dateien im "src"-Verzeichnis hinzu
file(GLOB SRC_FILES "src/*.cpp")

# Erstelle die ausführbare Datei mit den Quellcode-Dateien und Header-Dateien
add_executable(WCG ${HEADER_FILES} ${SRC_FILES})

target_include_directories(WCG PRIVATE inc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET WCG PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
