# Füge alle Header-Dateien im "inc"-Verzeichnis hinzu
file(GLOB HEADER_FILES "../inc/*.h")

# Füge alle Quellcode-Dateien im "src"-Verzeichnis hinzu
file(GLOB SRC_FILES "*.cpp")

# Erstelle die ausführbare Datei mit den Quellcode-Dateien und Header-Dateien
add_executable(OSC ${HEADER_FILES} ${SRC_FILES})

target_include_directories(OSC PRIVATE ../inc)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET OSC PROPERTY CXX_STANDARD 20)
endif()

# TODO: Fügen Sie bei Bedarf Tests hinzu, und installieren Sie Ziele.
