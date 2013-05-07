// PathStrAnalizer.cpp
//
//  パス文字列解析クラス実装部
//　ver 1.00
//
//  製作者 : IKD (2007. 9. 17)
//  HP     : http://marupeke296.com/
//

#pragma warning ( disable : 4996 )

#include "PathStrAnalizer.h"
#include <memory.h>

using namespace Dix;

const TCHAR PathStrAnalizer::nullStr_g = 0;

PathStrAnalizer::PathStrAnalizer( TCHAR* pathName ) :
directoryNum_( 0 ),
driveName_( 0 ),
pathValidate_( false )
{
	memset( directoryList_, 0, sizeof( directoryList_ ) );
	memset( pathName_, 0, sizeof( pathName_ ) );
	memset( fileName_, 0, sizeof( fileName_ ) );
	memset( extName_, 0, sizeof( extName_ ) );
	memset( fullFileName_, 0, sizeof( fullFileName_ ) );

	// ディレクトリパーサーにかける
	if ( pathName && _tcslen( pathName ) )
		pathValidate_ = startDirectoryParser( pathName );
}

PathStrAnalizer::~PathStrAnalizer() {
	size_t i;
	for ( i = 0; i < MAXDIRECTORYLISTNUM; i++ ) {
		safeDeleteDirectory( directoryList_[i] );
	}
}


// ファイルパス登録
bool PathStrAnalizer::regist( const TCHAR *pathName ) {
	pathValidate_ = startDirectoryParser( pathName );
	return pathValidate_;
}


// 登録されたパスは妥当か？
bool PathStrAnalizer::validatePathName() {
	return pathValidate_;
}


// ディレクトリパース開始
bool PathStrAnalizer::startDirectoryParser( const TCHAR* pathName ) {
	size_t sz = _tcslen( pathName );
	if( sz == 0 || sz > FULLPATHLENGTH-1 )
		return false;
	size_t prepos = 0;		// パースポジション

	// -- ドライブ名チェック -- //
	TCHAR driveName[DRIVELENGTH];
	bool isDrive = checkDriveName	( pathName, sz, 0, driveName );
	if( isDrive )
		prepos += DRIVELENGTH - 1;

	// -- ディレクトリチェック -- //
	TCHAR *directList[MAXDIRECTORYLISTNUM];
	memset( directList, 0, sizeof( TCHAR* ) * MAXDIRECTORYLISTNUM );
	size_t curListNum = 0;
	if ( isDrive ) {
		// ドライブ名をディレクトリの先頭に登録
		directList[0] = new TCHAR[ DRIVELENGTH ];
		memset( directList[0], 0, sizeof( TCHAR ) * DRIVELENGTH );
		_tcsncpy( directList[ 0 ], driveName, DRIVELENGTH-2 );	// デリミタは除く
		curListNum++;
	}
	size_t num = 0;
	while( prepos < sz ) {
		size_t yenDelim = findFirstOf( pathName+prepos, sz - prepos, L'\\' );
		size_t slashDelim = findFirstOf( pathName+prepos, sz - prepos,  L'/' );
		num = yenDelim < slashDelim ? yenDelim : slashDelim;
		if ( num != CANNOT_FIND_CHAR ) {
			// ディレクトリが存在
			if ( num == 0 || !checkFileName( pathName+prepos, num ) ) {
				// 不正なディレクトリ名が見つかった
				size_t i;
				for ( i = 0; i < curListNum ; i++ ) {
					safeDeleteDirectory( directList[ i ] );
				}
				return false;
			}
			directList[ curListNum ] = new TCHAR[ num+1 ];
			memset( directList[ curListNum ], 0, sizeof( TCHAR ) * ( num + 1 ) );
			_tcsncpy( directList[ curListNum ], pathName+prepos, num );
			prepos += num + 1;	// デリミタ飛ばし
			curListNum++;
		}
		else {
			// ファイル名として登録
			if ( !setFullFileName( pathName + prepos ) ) {
				size_t i;
				for ( i = 0; i < curListNum ; i++ ) {
					safeDeleteDirectory( directList[ curListNum ] );
				}
				return false;  // ファイル名として認められなかった
			}
			break;
		}
	}

	// ドライブ名を登録
	if( isDrive ) {
		driveName_ = driveName[0];
	}
	else {
		driveName_ = L'0';
	}

	// ディレクトリリストを登録
	size_t i;
	for ( i = 0; i < curListNum; i++ ) {
		if ( directoryList_[i] )
			safeDeleteDirectory( directoryList_[i] );
		directoryList_[i] = directList[i];
	}
	directoryNum_ = curListNum;

	// フルパス名を作成
	updateFullName();

	return true;
}


// フルパス名を生成登録
void PathStrAnalizer::createFullPath( const TCHAR delim ) {
	memset( pathName_, 0, FULLPATHLENGTH );
	size_t fullPos = 0;
	size_t i;
	for ( i = 0; i < directoryNum_; i++ ) {
		size_t Dir_sz = _tcslen( directoryList_[i] );
		_tcsncpy( pathName_ + fullPos, directoryList_[i], Dir_sz );
		pathName_[ fullPos + Dir_sz ] = delim;
		fullPos += Dir_sz + 1;
	}
	_tcsncpy( pathName_ + fullPos, fileName_, _tcslen( fileName_ ) );
	if ( _tcslen( extName_ ) ) {
		*(pathName_ + fullPos + 1) = L'.';
		_tcsncpy( pathName_ + fullPos + 1, extName_, _tcslen( extName_ ) );
	}
}

// ドライブ名をチェック
bool PathStrAnalizer::checkDriveName( const TCHAR* pathName, size_t length, size_t pos, TCHAR outDriveName[] ) {
	if( length < 4 ) {
		// 絶対パスではない
		return false;
	}
	memset( outDriveName, 0, sizeof( TCHAR ) * DRIVELENGTH ); 

	// ドライブチェック
	TCHAR A = L'A', Z = L'Z', Co = L':';
	TCHAR a = L'a', z = L'z';
	TCHAR name = pathName[0];
	if( ( a <= name && name <= z )
		|| (A <= name && name <= Z ) ) {
		if ( pathName[1] == Co && checkDriveDelim( pathName[2] ) ) {
			// ドライブ名検出完了
			_tcsncpy( outDriveName, pathName, DRIVELENGTH-1 );
			return true;
		}
	}
	return false;
}

// ドライブデリミタチェック
bool PathStrAnalizer::checkDriveDelim( TCHAR delim ) {
	if ( delim == '\\' || delim == '/' )
		return true;
	return false;
}

// 初文字検索
size_t PathStrAnalizer::findFirstOf( const TCHAR *str, size_t sz, const TCHAR c ) {
	size_t i;
	for ( i = 0; i < sz; i++ ) {
		if ( str[i] == c ) {
			return i;
		}
	}
	return CANNOT_FIND_CHAR;
}

// 終文字検索
size_t PathStrAnalizer::findLastOf( const TCHAR *str, size_t sz, const TCHAR c ) {
	size_t i;
	for ( i = sz-1; i != -1; i-- ) {
		if ( str[i] == c ) {
			return i;
		}
	}
	return CANNOT_FIND_CHAR;
}

// ヒットしない文字を終端から検索
size_t PathStrAnalizer::findLastNotOf( const TCHAR *str, size_t sz, const TCHAR c ) {
	size_t i;
	for ( i = sz-1; i != -1; i-- ) {
		if ( str[i] != c ) {
			return i;
		}
	}
	return CANNOT_FIND_CHAR;
}


// ドライブ名を登録
bool PathStrAnalizer::setDriveName( TCHAR driveName ) {
	// 相対パスであればドライブ名変更をしない
	if ( !isAbsolutePath() )
		return false;

	// ドライブチェック
	TCHAR A = L'A', Z = L'Z';
	TCHAR a = L'a', z = L'z';
	if( ( a <= driveName && driveName <= z )
		|| (A <= driveName && driveName <= Z ) )
	{
		if ( driveName_ != driveName ) {
			driveName_ = driveName;
			updateFullName();
		}
		return true;
	}
	return false;
}

// ファイル名をチェック
bool PathStrAnalizer::checkFileName( const TCHAR *fileName ) {
	// ファイル名として扱えない文字が含まれていないかをチェック
	size_t sz = _tcslen( fileName ), i;
	if( sz > MAXFILELENGTH )
		return false;

	for ( i = 0; i < sz; i++ ) {
		TCHAR c = fileName[i];
		if ( c == L'\\' || c == L'/' || c == L'?'
			|| c == L':' || c == L'*' || c == L'"'
			|| c == L'|' || c == L'<' || c == L'>' || c == '\'' )
		{
			return false;	// ファイル名に使えない文字が入っていた
		}
	}
	return true;
}


// ファイル名をチェック
bool PathStrAnalizer::checkFileName( const TCHAR *fileName, size_t size ) {
	TCHAR tmp[MAXFILELENGTH];
	memset( tmp, 0, sizeof( TCHAR ) * MAXFILELENGTH );
	_tcsncpy( tmp, fileName, size );
	return checkFileName( tmp );
}


// フルファイル名を登録
bool PathStrAnalizer::setFullFileName( const TCHAR* fileName ) {
	if ( !checkFileName( fileName ) )
		return false;
	size_t sz = _tcslen( fileName );
	// 終端の[.]をチェック
	size_t pos = sz;
	if ( fileName[sz-1] == L'.' ) {
		pos = findLastNotOf( fileName, sz, L'.' );
	}

	// 拡張子チェック
	memset( extName_, 0, sizeof( extName_ ) );
	size_t extpos = findLastOf( fileName, pos, L'.' );
	if ( extpos != CANNOT_FIND_CHAR ) {
		setExtName( fileName+extpos+1 );
		setFileName( fileName, extpos );
	}
	else {
		setFileName( fileName, pos );
	}

	updateFullName();

	return true;
}

// ファイル名を登録
bool PathStrAnalizer::setFileName( const TCHAR* fileName ) {
	if ( !checkFileName( fileName ) )
		return false;
	size_t sz = _tcslen( fileName );
	memset( fileName_, 0, sizeof( fileName_ ) );

	// 終端の[.]があれば除いて登録
	if ( fileName[sz-1] == L'.' ) {
		size_t pos = findLastNotOf( fileName, sz, L'.' );
		_tcsncpy( fileName_, fileName, pos+1 );
	}
	else {
		_tcsncpy( fileName_, fileName, sz );
	}

	updateFullName();
	return true;
}

// ファイル名を登録
bool PathStrAnalizer::setFileName( const TCHAR* fileName, size_t size ) {
	size_t sz = _tcslen( fileName );
	TCHAR tmpFileName[MAXFILELENGTH];
	memset( tmpFileName, 0, sizeof( TCHAR ) * MAXFILELENGTH );
	_tcsncpy( tmpFileName, fileName, ( sz < size )? sz : size );
	setFileName( tmpFileName );
	return true;
}

// 拡張子名を登録
bool PathStrAnalizer::setExtName( const TCHAR* extName ) {
	size_t sz = _tcslen( extName );
	if( sz > MAXEXTLENGHT )
		return false;  // 拡張子長オーバー

	if ( !checkFileName( extName ) )
		return false;

	memset( extName_, 0, sizeof( extName_ ) );
	// 終端の[.]があれば除いて登録
	if ( extName[sz-1] == L'.' ) {
		size_t pos = findLastNotOf( extName, sz, L'.' );
		_tcsncpy( extName_, extName, pos+1 );
	}
	else {
		_tcsncpy( extName_, extName, sz );
	}
	updateFullName();
	return true;
}


// フルパス名を取得
const TCHAR* PathStrAnalizer::getFullPathName() const {
	return pathName_;
}

// フルファイル名を取得
const TCHAR* PathStrAnalizer::getFullFileName() const {
	return fullFileName_;
}

// ファイル名を取得
const TCHAR* PathStrAnalizer::getFileName() const {
	return fileName_;
}

// 拡張子名を取得
const TCHAR* PathStrAnalizer::getExtName() const {
	return extName_;
}

// ディレクトリ名を取得
const TCHAR* PathStrAnalizer::getDirectoryName( size_t level ) const {
	if ( level >= directoryNum_ )
		return &nullStr_g;
	return directoryList_[level];
}

// ディレクトリ数を取得
size_t PathStrAnalizer::getDirectoryNum() const {
	return directoryNum_;
}

// フルパス系をアップデート
void PathStrAnalizer::updateFullName() {
	size_t i;
	// 絶対パスであればドライブ名を変更する
	if ( isAbsolutePath() && directoryList_[0] )
		directoryList_[0][0] = driveName_;

	memset( pathName_, 0, sizeof(TCHAR) * FULLPATHLENGTH );
	for ( i = 0; i < directoryNum_; i++ ) {
		_tcsncat( pathName_, directoryList_[i], _tcslen(directoryList_[i]) );
		_tcsncat( pathName_, _T("/"), 1 );
	}

	memset( fullFileName_, 0, sizeof(TCHAR) * MAXFILELENGTH );
	_tcsncat( fullFileName_, fileName_, _tcslen(fileName_) );
	if ( isExt() ) {
		_tcsncat( fullFileName_, _T("."), 1 );
		_tcsncat( fullFileName_, extName_, _tcslen(extName_) );
	}
	_tcsncat( pathName_, fullFileName_, _tcslen(fullFileName_) );
}

// 拡張子があるかチェック
bool PathStrAnalizer::isExt() {
	if ( _tcslen( extName_ ) )
		return true;
	return false;
}


// 絶対パスか？
bool PathStrAnalizer::isAbsolutePath() {
	return ( driveName_ != L'0' );
}

// ディレクトリを挿入
bool PathStrAnalizer::insert( size_t level, const TCHAR* directoryName ) {
	size_t num = getDirectoryNum();
	if ( isAbsolutePath() ) {
		// 絶対パスの場合
		// ・ ルートへの挿入
		// ・ 最下層numより1つ下(num+1の位置)以下を指定
		// の場合はエラー
		if ( level == 0 || level >= num+1 ) {
			return false;
		}
	}
	else {
		// 相対パスの場合
		// ・ ディレクトリが無くてルート階層を指定した場合は有効
		// ・ ディレクトリがある状態では最下層より2つ下（num + 1）を指定したらエラー
		if ( num == 0 ) {
			if ( level != 0 )
				return false;
		}
		else {
			if ( level >= num + 1 ) {
				return false;
			}
		}
	}

	// 挿入箇所の後ろを移動
	memmove( directoryList_ + level + 1, directoryList_ + level, sizeof( TCHAR* ) * ( num - level + 1 ) );
	directoryList_[level] = new TCHAR[ _tcslen( directoryName ) + 1 ];
	_tcscpy( directoryList_[level], directoryName );
	directoryList_[level][_tcslen( directoryName )] = L'\0';	// 終端ナル文字追加
	directoryNum_++;

	updateFullName();

	return true;
}

// ディレクトリを設定
bool PathStrAnalizer::setDirectoryName( size_t level, const TCHAR* directoryName ) {
	size_t num = getDirectoryNum();
	if ( num <= level )
		return false;
	if ( level == 0 && isAbsolutePath() )
		return false;

	// 変更
	safeDeleteDirectory( directoryList_[level] );
	directoryList_[level] = new TCHAR[ _tcslen( directoryName ) + 1 ];
	_tcscpy( directoryList_[level], directoryName );
	directoryList_[level][_tcslen( directoryName )] = L'\0';	// 終端ナル文字追加

	updateFullName();

	return true;
}

// ディレクトリを削除
bool PathStrAnalizer::deleteDirectory( size_t level ) {
	size_t num = getDirectoryNum();
	// 絶対パスの場合はnum=1では消す物が無いのでエラー
	// またドライブは消せない
	if ( isAbsolutePath() ) {
		if ( num <= 1 || level >= num || level == 0 )
			return false;
	}
	else {
		// 相対パスの場合は消せるディレクトリが無いとエラー
		if ( level >= num )
			return false;
	}

	// 削除
	safeDeleteDirectory( directoryList_[level] );
	memmove( directoryList_ + level, directoryList_ + level + 1, sizeof( TCHAR* ) * ( num - level ) );
	directoryList_[directoryNum_ - 1] = PATHSTRANALIZER_SKIP_PTR;
	directoryNum_--;

	updateFullName();

	return true;
}

// ディレクトリセーフデリート
void PathStrAnalizer::safeDeleteDirectory( TCHAR* deleteDirectory ) {
	if( deleteDirectory && deleteDirectory != PATHSTRANALIZER_SKIP_PTR )
		delete[] deleteDirectory;
}