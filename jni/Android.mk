LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := hellondk
LOCAL_LDLIBS    := -llog
LOCAL_SRC_FILES := mylib.c

include $(BUILD_SHARED_LIBRARY)
