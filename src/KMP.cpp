// 2년전 자료구조 학점을 위협했던 알고리즘이다.	
// 주어진 문자열에 대하여 패턴을 찾아내는 알고리즘이며 O(문자열 길이 + 패턴 길이)의 시간복잡도로 작동한다.
// 현재 위치에서 패턴과 비교하다가 실패하면 검사할 패턴 위치를 지금까지 검사한것들중 최 서로 일치하는 접두사와 접미사의 최장길이로 이동시키자

/*
  실패함수를 만드는 과정.
  패턴의 부분문자열에서 길이와 내용이 일치하는 접두사와 접미사의 최장길이를 저장하자
  (단 prefix가 부분문자열 전체를 포함하면 안된다)
*/

for (int i = 1, j = 0; i < p.size(); i++) {
	while (j > 0 && p[i] != p[j])j = fail[j - 1];
	if (p[i] == p[j])fail[i] = ++j;
}

/*
  패턴을 찾아가는 과정
  현재 위치에서 문자열이 패턴이 일치하지 않으면 검사할 다음 패턴위치를 현재까지 검사한 것들중 공통 접두사와 접미사의 최장 위치로 이동시킨다.
*/

for (int i = 0, j = 0; i < t.size(); i++) {
	while (j > 0 && t[i] != p[j])j = fail[j - 1]; // 일치하지 않는다면 검사한 것들중 공통 접두사와 접미사의 최장 위치로 이동시킨다.
	if (t[i] == p[j]) {
		if (j == p.size() - 1) {
			ans.push_back(i - p.size() + 2);
			j = fail[j];
		}
		else j++;
	}
}
