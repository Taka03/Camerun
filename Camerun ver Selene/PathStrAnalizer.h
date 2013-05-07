#ifndef IKD_PATHSTRANALIZER_H
#define IKD_PATHSTRANALIZER_H
// PathStrAnalizer.h
//
//  パス文字列解析クラス
//　ver 1.00
//
//  製作者 : IKD (2007. 9. 17)
//  HP     : http://marupeke296.com/
//

#include <tchar.h>
#include <windows.h>

#define DRIVELENGTH 4
#define FULLPATHLENGTH 512
#define MAXFILELENGTH 256
#define MAXEXTLENGHT 20
#define MAXDIRECTORYLISTNUM 128
#define CANNOT_FIND_CHAR 0xffffffff
#define PATHSTRANALIZER_SKIP_PTR ((TCHAR*)(LONG_PTR)0xffffffff)

namespace Dix {
	class PathStrAnalizer {
	public:
		PathStrAnalizer( TCHAR* pathName = 0 );
		~PathStrAnalizer();

	private:
		// ディレクトリパーサー実行
		bool startDirectoryParser( const TCHAR* pathName );
		// ドライブ名チェック
		bool checkDriveName( const TCHAR* pathName, size_t length, size_t pos,  TCHAR outDraiveName[DRIVELENGTH] );
		// ドライブデリミタチェック
		bool checkDriveDelim( TCHAR delim );
		// 初文字検索
		size_t findFirstOf( const TCHAR *str, size_t sz, const TCHAR c );
		// 終文字検索
		size_t findLastOf( const TCHAR *str, size_t sz, const TCHAR c );
		// ヒットしない文字を終端から検索
		size_t findLastNotOf( const TCHAR *str, size_t sz, const TCHAR c );
		// ファイル名をチェック
		bool checkFileName( const TCHAR *fileName );
		// ファイル名をチェック
		bool checkFileName( const TCHAR *fileName, size_t size );
		// フルパス名を生成登録
		void createFullPath( const TCHAR delim = L'/' );
		// フルパス系をアップデート
		void updateFullName();
		// 拡張子があるかチェック
		bool isExt();
		// ディレクトリセーフデリート
		void safeDeleteDirectory( TCHAR* deleteDirectory );

	public:
		// ディレクトリを削除
		bool deleteDirectory( size_t level );
		// ディレクトリ名を取得
		const TCHAR* getDirectoryName( size_t level ) const;
		// ディレクトリ数を取得
		size_t getDirectoryNum() const;
		// 拡張子名を取得
		const TCHAR* getExtName() const;
		// ファイル名を取得
		const TCHAR* getFileName() const;
		// フルファイル名を取得
		const TCHAR* getFullFileName() const;
		// フルパス名を取得
		const TCHAR* getFullPathName() const;
		// ディレクトリを挿入
		bool insert( size_t level, const TCHAR* directoryName );
		// 絶対パスか？
		bool isAbsolutePath();
		// ファイルパス登録
		bool regist( const TCHAR *pathName );
		// ディレクトリを設定
		bool setDirectoryName( size_t level, const TCHAR* directoryName );
		// ドライブ名を登録
		bool setDriveName( TCHAR driveName );
		// 拡張子名を登録
		bool setExtName( const TCHAR* extName );
		// ファイル名を登録
		bool setFileName( const TCHAR* fileName );
		bool setFileName( const TCHAR* fileName, size_t size );
		// フルファイル名を登録
		bool setFullFileName( const TCHAR* fileName );
		// 登録されたパスは妥当か？
		bool validatePathName();

	private:
		bool pathValidate_;
		static const TCHAR nullStr_g;
		size_t directoryNum_;
		TCHAR *directoryList_[MAXDIRECTORYLISTNUM];
		TCHAR pathName_[FULLPATHLENGTH];
		TCHAR driveName_;
		TCHAR fullFileName_[MAXFILELENGTH];
		TCHAR fileName_[MAXFILELENGTH];
		TCHAR extName_[MAXEXTLENGHT];
	};
}

#endif