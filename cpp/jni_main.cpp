#include <jni.h>
#include <iostream>
#include "org_example_DatabaseConnector.h"

JNIEnv* create_vm(JavaVM** jvm) {
    JNIEnv* env;
    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    // 当前目录作为类路径
    char str[] = "-Djava.class.path=/Users/lixinzhuang1/IdeaProjects/JNI-demo/src/main/java:/Users/lixinzhuang1/.m2/repository/com/microsoft/sqlserver/mssql-jdbc/12.4.2.jre8/mssql-jdbc-12.4.2.jre8.jar";
    options[0].optionString = str;
    // 设置 JNI版本
    vm_args.version = JNI_VERSION_1_8;
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = JNI_FALSE;
    int ret = JNI_CreateJavaVM(jvm, (void**)&env, &vm_args);
    if (ret < 0) {
        std::cerr << "Unable to launch JVM" << std::endl;
    }
    return env;
}

int main() {
    JavaVM* jvm;
    JNIEnv* env = create_vm(&jvm);
    if (env == nullptr) return 1;

    // 查找Java类
    jclass cls = env ->FindClass("org/example/DatabaseConnector");
    if (cls != nullptr) {
        // 获取方法ID
        jmethodID  mid = env ->GetStaticMethodID(cls, "queryDatabase", "()Ljava/lang/String;");
        if (mid != nullptr) {
            // 调用静态方法
            jstring result = (jstring)env ->CallStaticObjectMethod(cls, mid);
            const char* str = env ->GetStringUTFChars(result, nullptr);
            if (str != nullptr) {
                std::cout << "Query Result:\n" << str << std::endl;
                env ->ReleaseStringUTFChars(result, str); // 释放字符串
            }
        }
    }
    jvm -> DestroyJavaVM();
    return 0;
}
