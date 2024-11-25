#pragma once
#include <vector>
#include <afxwin.h> // CString 포함

class CMessageManager {
private:
    std::vector<CString> messages; // 메시지 목록
    const int maxMessages = 2;     // 최대 메시지 개수

public:
    static CMessageManager& GetInstance() {
        static CMessageManager instance; // 싱글톤
        return instance;
    }

    void AddMessage(const CString& message) {
        if (messages.size() >= maxMessages) {
            messages.erase(messages.begin()); // 오래된 메시지 제거
        }
        messages.push_back(message);
    }

    const std::vector<CString>& GetMessages() const {
        return messages;
    }

private:
    CMessageManager() {} // 생성자 비공개
};
