file(GLOB_RECURSE SOURCES_FILES ./*.c)

idf_component_register(SRCS ${SOURCES_FILES}
                    INCLUDE_DIRS "include")
