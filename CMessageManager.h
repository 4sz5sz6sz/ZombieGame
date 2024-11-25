#pragma once
#include <vector>
#include <afxwin.h> // CString ����

class CMessageManager {
private:
    std::vector<CString> messages; // �޽��� ���
    const int maxMessages = 2;     // �ִ� �޽��� ����

public:
    static CMessageManager& GetInstance() {
        static CMessageManager instance; // �̱���
        return instance;
    }

    void AddMessage(const CString& message) {
        if (messages.size() >= maxMessages) {
            messages.erase(messages.begin()); // ������ �޽��� ����
        }
        messages.push_back(message);
    }

    const std::vector<CString>& GetMessages() const {
        return messages;
    }

private:
    CMessageManager() {} // ������ �����
};
