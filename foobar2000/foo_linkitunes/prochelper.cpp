#include "prochelper.h"

// ���݋N�����Ă���v���Z�X���̃��X�g��Ԃ�
ModuleNameList getModuleList() {
	ModuleNameList module_name_list;
	// �X�i�b�v�V���b�g���擾
	HANDLE snapshot = ::CreateToolhelp32Snapshot(
		TH32CS_SNAPPROCESS, 0
		);
	if (snapshot == INVALID_HANDLE_VALUE)
		throw std::exception();

	// �v���Z�X�̏��𑖍�
	PROCESSENTRY32W entry;
	entry.dwSize = sizeof(entry);
	BOOL has_entry = ::Process32FirstW(snapshot, &entry);
	while (has_entry) {
		module_name_list.push_back(entry.szExeFile);
		has_entry = ::Process32NextW(snapshot, &entry);
	}
	::CloseHandle(snapshot);

	return module_name_list;
}