#pragma once

#include <fstream>
#include <map>
#include <Utility/cSingletonAble.h>

namespace Log
{
	//! @fn   cLog
	//! @brief Log�̓f���o���������s���܂�
	//! @note 
	//!       
	//! @date 2017-11-09
	//! @author Taka Nomoto

	class cLog
	{
	public:
		cLog(){}

		cLog(const std::string& filename)
		{
			open(filename);
		}

		//File���J���܂�
		//File���Ȃ����́A�����I�ɐ�������܂�
		void open(const std::string& filename);
		
		//File���܂�
		//���Ȃ��Ă����v�����ǂ����ƕ���悤��
		void close();

		//Log�̓f���o��
		void writeLog(std::string str);

		std::ofstream fst;

	};
	//! @fn   cLogManager
	//! @brief Log�̊Ǘ����s���܂�
	//! @note 
	//!       �g���� : 
	//!        ex)
	//!             add("test")
	//!              ->Key -> test ��Log���쐬
	//!                test.log��Log/���t/�̏ꏊ�ɐ�������܂�
	//!
	//!             write("test","��������")
	//!              -> test.log�Ɂ@"��������"���f���o����܂�
	//!           
	//! @date 2017-11-09
	//! @author Taka Nomoto
	class cLogManager : public Utility::cSingletonAble<cLogManager>
	{
	public:
		
		void add(const std::string filename);

		void close();

		void writeLog(const std::string& filename, const std::string& str);

	private:
		std::map<std::string, cLog> logs;
	};

}
