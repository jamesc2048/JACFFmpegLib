TEMPLATE = subdirs

SUBDIRS += JACFFmpegLib \
    TestProject

TestProject.depends += JACFFmpegLib
