# Movie Recommender

> C++로 구현한 콘솔 기반 영화 추천 시스템 — 코사인 유사도 기반 협업 필터링(User-Based Collaborative Filtering)

---

## 프로젝트 개요

사용자의 영화 평점 데이터를 분석하여 **코사인 유사도**로 취향이 비슷한 유저를 찾고, 그 유저가 높게 평가한 영화를 추천하는 C++ 콘솔 애플리케이션입니다.  
영화·사용자·평점 데이터를 CSV 파일로 영구 저장하며, OOP 설계 원칙(캡슐화·상속·다형성)을 적용하였습니다.

---

## 빌드 방법

**요구 사항**
- g++ (C++17 이상)
- make

```bash
# 저장소 클론
git clone https://github.com/chouflavor/movie-recommender.git
cd movie-recommender

# 빌드
make

# 빌드 결과물 삭제
make clean
```

---

## 실행 방법

```bash
# 빌드 후 실행
make run

# 또는 직접 실행
./movie_recommender
```

> 프로그램이 시작되면 `data/` 폴더의 `movies.csv`, `users.csv`, `ratings.csv`를 자동으로 불러옵니다.  
> 종료(0번) 시 변경 사항이 자동으로 저장됩니다.

---

## 주요 기능

| 번호 | 기능 | 설명 |
|------|------|------|
| 1 | 영화 추가 | 제목·장르·출시 연도를 입력해 영화 등록 |
| 2 | 제목 검색 | 키워드 대소문자 무관 부분 일치 검색 |
| 3 | 전체 목록 출력 | 등록된 모든 영화 출력 |
| 4 | 정렬 출력 | 평점순 / 가나다순 / 최신순 선택 정렬 |
| 5 | 사용자 추가 | 이름·이메일로 사용자 등록 |
| 6 | 사용자 목록 | 등록된 사용자 전체 출력 |
| 7 | 평점 입력 | 유저 ID·영화 ID·점수(0~5)로 평점 등록 |
| 8 | 영화별 평점 | 등록된 모든 평점 목록 출력 |
| 9 | 맞춤 추천 | 코사인 유사도 기반 협업 필터링 추천 (장르 필터 선택 가능) |
| 10 | 통계 | 전체 평균 평점 / 장르별 평균 / Top 10 영화 |

---

## 클래스 구조

```
BaseManager (abstract)
├── MovieManager   — 영화 데이터 관리 (vector<Movie>)
├── UserManager    — 사용자 데이터 관리 (vector<User>)
└── RatingManager  — 평점 데이터 관리 (vector<Rating>)

MovieSystem        — 전체 시스템 조합·메뉴 제어 (MovieManager, UserManager, RatingManager 보유)
Recommender        — 코사인 유사도 계산 및 추천 로직 (RatingManager 참조)

Movie              — 영화 엔티티 (id, title, genre, year, totalRating, ratingCount)
User               — 사용자 엔티티 (id, name, email)
Rating             — 평점 엔티티 (userID, movieID, score)
```

### 상속 관계
```
BaseManager
    ↑ (IS-A)
    ├── MovieManager
    ├── UserManager
    └── RatingManager
```

`BaseManager`는 `loadFromFile()`, `saveToFile()`, `size()`를 순수 가상 함수로 선언하여, 각 Manager가 자신의 데이터 형식에 맞게 구현하도록 강제합니다.

---

## 추천 알고리즘

**User-Based Collaborative Filtering + Cosine Similarity**

$$\text{similarity}(A, B) = \frac{\vec{r_A} \cdot \vec{r_B}}{|\vec{r_A}||\vec{r_B}|}$$

1. 타겟 유저와 모든 유저 간 코사인 유사도 계산
2. 유사도 상위 K명(기본 K=3) 선택
3. K명이 평가했으나 타겟 유저가 보지 않은 영화 수집
4. 수집된 영화를 점수 합산 기준 내림차순 정렬 후 N편(기본 N=3) 추천
5. 장르 필터 입력 시 해당 장르 영화만 추천 후보로 제한

> 공통 평점 영화가 없어 내적이 0인 경우 패널티 점수 `-2.0`을 부여합니다.

---

## 데이터 파일 형식

`data/movies.csv`
```
id,title,genre,year
1,인셉션,Sci-Fi,2010
```

`data/users.csv`
```
id,name,email
1,charlie,kirky@email.com
```

`data/ratings.csv`
```
userId,movieId,score
1,1,5
```

---

## 확장 기능 (구현 가능 방향)

- **Item-Based CF**: 영화 간 유사도 계산으로 아이템 기반 추천 추가
- **평점 정규화**: 사용자별 평균 평점 편차를 보정하는 Adjusted Cosine 유사도 적용
- **페르소나 태그**: 사용자 선호 장르 프로필 저장 및 가중치 반영
- **데이터베이스 연동**: CSV → SQLite 또는 외부 DB로 확장
- **성능 최적화**: 유사도 사전 계산 및 캐싱으로 O(N²) 병목 해소

---

## 작성자

| 이름 | GitHub |
|------|--------|
| chouflavor | [@chouflavor](https://github.com/chouflavor) |
