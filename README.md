# 이재민 | C++ 게임·엔진 개발 포트폴리오

C++ 팀 게임의 공통 객체·충돌 시스템 구현 경험을 바탕으로 OpenGL 렌더링과 엔진 기초 개발을 이어가고 있습니다.

- 목표 분야: **게임 엔진·렌더링·물리 / C++ 게임 클라이언트 신입**
- [Notion 포트폴리오](https://app.notion.com/p/53056576e7d6454f9b8c84224bc99138)
- [최근 OpenGL 저장소](https://github.com/jaemin-lee00/LearnOpenGL)

## 대표 작업

### Dungeon Maker — C++ 팀 게임

2019년 3인 팀 프로젝트에서 Main/Lead Programmer로 공통 객체 구조와 충돌 판정·보정, 메인 프로그래밍을 담당했습니다.

- 위치·크기·속도를 관리하는 공통 객체 구조.
- 원-원, 원-사각형, 사각형-사각형 충돌과 벽 충돌 처리.
- [역할·프로젝트 설명](GameProject/ReadMe.txt)
- [충돌 시스템 코드](GameProject/Project/cs120_doodle/System.cpp)
- [캐릭터·물리 관련 코드](GameProject/Project/cs120_doodle/Player.cpp)

외부 **doodle framework**와 팀원 코드를 함께 사용했습니다. 담당 범위는 README와 각 소스의 작성자 표기를 기준으로 구분합니다.

### OpenGL 렌더링·엔진 기초 — 개인 학습·구현

카메라·좌표 변환·텍스처·GLSL·렌더 상태를 다루며 FBO 렌더 패스를 확장하고 있습니다.

- 최신 작업은 별도 [LearnOpenGL 저장소](https://github.com/jaemin-lee00/LearnOpenGL)에서 확인할 수 있습니다.
- [공유된 FBO 추가 커밋](https://github.com/jaemin-lee00/LearnOpenGL/commit/8fbb710dfeab6817dd8c1b4ba2883e0e7e394484).
- 2026-10-16 최신 로컬 C++17 소스의 MSVC 구문검사를 통과했습니다. 로컬 후속 작업은 원격 공유 코드와 차이가 있으며 전체 빌드·실행·GPU 화면 검증은 별도 단계입니다.

### IPTV 음성 인식·프로그램 통합 — Python

2024~2025년 프로젝트 기록에서 5인 팀의 Client Programmer로 STT와 프로그램 통합 관련 개발을 담당했습니다.

- [역할·시연 영상·발표자료](https://app.notion.com/p/18532f9605b5808ebb78dee7c6ef3258)

## 이 저장소의 구성

| 경로 | 내용 |
|---|---|
| [GameProject](GameProject) | C++ 팀 게임 Dungeon Maker |
| [LearnOpenGL-VisualStudio](LearnOpenGL-VisualStudio) | 이전 OpenGL 학습 자료. 최신 작업은 별도 저장소 참고 |
| [ProjectH](ProjectH) | Unity 프로토타입 코드 |
| [OLC](OLC) | OneLoneCoder의 외부 엔진을 활용한 학습 자료 |

OLC와 외부 프레임워크의 저작권·크레딧은 원문을 따릅니다. 외부 엔진 자체를 본인이 작성한 엔진으로 소개하지 않습니다.
