[ex00]  
Heredocを>>の代わりに  
mapは*でなくても良い  
サイズ決まっている  
IsNumeric “”の時trueになってしまう  
year > 1 紀元  
std::map<std::string, float>に対してtypedefする  
4-2-2文字を確認 or date型  
dir はopenできるできるけどreadできない  
-1-1 | 1 //error  
1-1-1 | inf  
9999-02-31 | 1  
20000-01-01 | 1  
420-01-01 | 1 //新しいものとして認識されてしまう  
未来の日付に対しては最新のものを使う  
lower-bound関数  
過去の存在しないものに対してもエラー  
if (date > key) break ;  
curlでdataをダウンロード  

[ex01]  
devide -> divde  
class内のstaticはない方が良い（スレッドセーフティーも）  
exitはない方が良い(throw した方が良い)  
どこでエラーがあったかわかった方が良い  
strchrはfindで良い  
INT_MIN / -1はクラッシュ  
stack<int>でも良い  
オーバーフロー  
8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * 2 *   
"-8 8 8 8 8 8 8 8 8 8 * * * * * * * * * * -1 /"

[ex02]  
doubleをclock_tに揃える  
関数をもう少しprivateに  
sort系の関数、カノニカルフォームをプライベートに(大元のみをpublicに)  
strcmpを == にコンストラクタで変数の初期化  
checksorted 両方イテレーターに  
比較を少なく  
pushをする時間は含めない

