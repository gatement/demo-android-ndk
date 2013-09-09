#include <string.h>
#include <jni.h>
#include <android/log.h>

JNIEnv* jniEnv = NULL;

jclass TestProvider = NULL;
jobject mTestProvider = NULL;
jmethodID getTime = NULL;
jmethodID sayHello = NULL;

int GetProviderInstance(jclass obj_class);

int InitProvider() {
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  1" );

	if(jniEnv == NULL) {
		return 0;
	}

	if(TestProvider == NULL) {
		TestProvider = (*jniEnv)->FindClass(jniEnv,"net/johnsonlau/android/hellondk/TestProvider");
		if(TestProvider == NULL){
			return -1;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  2 ok" );
	}

	if (mTestProvider == NULL) {
		if (GetProviderInstance(TestProvider) != 1) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			return -1;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  3 ok" );
	}

	if (getTime == NULL) {
		getTime = (*jniEnv)->GetStaticMethodID(jniEnv, TestProvider, "getTime","()Ljava/lang/String;");
		if (getTime == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			return -2;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  4 ok" );
	}

	if (sayHello == NULL) {
		sayHello = (*jniEnv)->GetMethodID(jniEnv, TestProvider, "sayHello","(Ljava/lang/String;)V");
		if (sayHello == NULL) {
			(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
			(*jniEnv)->DeleteLocalRef(jniEnv, getTime);
			return -3;
		}
		__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  5 ok" );
	}

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  6" );
	return 1;

}

int GetProviderInstance(jclass obj_class) {

	if(obj_class == NULL) {
		return 0;
	}

	jmethodID construction_id = (*jniEnv)->GetMethodID(jniEnv, obj_class, "<init>", "()V");

	if (construction_id == 0) {
		return -1;
	}

	mTestProvider = (*jniEnv)->NewObject(jniEnv, obj_class, construction_id);

	if (mTestProvider == NULL) {
		return -2;
	}

	return 1;
}

void GetTime() {
	if(TestProvider == NULL || getTime == NULL) {
		int result = InitProvider();
		if (result != 1) {
			return;
		}
	}

	jstring jstr = NULL;
	char* cstr = NULL;
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin" );
	jstr = (*jniEnv)->CallStaticObjectMethod(jniEnv, TestProvider, getTime);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin2" );
	cstr = (char*) (*jniEnv)->GetStringUTFChars(jniEnv,jstr, 0);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "Success Get Time from Java , Value = %s",cstr );
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime End" );

	(*jniEnv)->ReleaseStringUTFChars(jniEnv, jstr, cstr);
	(*jniEnv)->DeleteLocalRef(jniEnv, jstr);
}

void SayHello() {
	if(TestProvider == NULL || mTestProvider == NULL || sayHello == NULL) {
		int result = InitProvider() ;
		if(result != 1) {
			return;
		}
	}

	jstring jstrMSG = NULL;
	jstrMSG =(*jniEnv)->NewStringUTF(jniEnv, "Hi,I'm From C");
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello Begin" );
	(*jniEnv)->CallVoidMethod(jniEnv, mTestProvider, sayHello,jstrMSG);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "SayHello End" );

	(*jniEnv)->DeleteLocalRef(jniEnv, jstrMSG);
}

int GetTime2(JNIEnv* jniEnv)
{
	jclass TestProvider = NULL;
	jmethodID getTime = NULL;

	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  1" );

	TestProvider = (*jniEnv)->FindClass(jniEnv,"net/johnsonlau/android/hellondk/TestProvider");
	if(TestProvider == NULL){
		return -1;
	}
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  2 ok" );

	getTime = (*jniEnv)->GetStaticMethodID(jniEnv, TestProvider, "getTime","()Ljava/lang/String;");
	if (getTime == NULL) {
		(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
		return -2;
	}
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "InitProvider Begin  4 ok" );

	jstring jstr = NULL;
	char* cstr = NULL;
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin" );
	jstr = (*jniEnv)->CallStaticObjectMethod(jniEnv, TestProvider, getTime);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime Begin2" );
	cstr = (char*) (*jniEnv)->GetStringUTFChars(jniEnv,jstr, 0);
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "Success Get Time from Java , Value = %s",cstr );
	__android_log_print(ANDROID_LOG_INFO, "JNIMsg", "GetTime End" );

	(*jniEnv)->ReleaseStringUTFChars(jniEnv, jstr, cstr);
	(*jniEnv)->DeleteLocalRef(jniEnv, jstr);

	//(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
	//(*jniEnv)->DeleteLocalRef(jniEnv, getTime);
}

jstring Java_net_johnsonlau_android_hellondk_MainActivity_myStr (JNIEnv* env, jobject thiz )
{
	jniEnv = env;

	GetTime2(env);
	//SayHello();

	/*(*jniEnv)->DeleteLocalRef(jniEnv, TestProvider);
	(*jniEnv)->DeleteLocalRef(jniEnv, mTestProvider);
	(*jniEnv)->DeleteLocalRef(jniEnv, getTime);
	(*jniEnv)->DeleteLocalRef(jniEnv, sayHello);

	TestProvider = NULL;
	mTestProvider = NULL;
	getTime = NULL;
	sayHello = NULL;
*/
   return (*env)->NewStringUTF(env, "ok.Lgh!");
}

