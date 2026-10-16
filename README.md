# 이재민 | C++ 게임·엔진 개발 포트폴리오

C++ 팀 게임의 공통 객체·충돌 시스템 구현 경험을 바탕으로 OpenGL 렌더링과 엔진 기초 개발을 이어가고 있습니다.

- 목표 분야: **게임 엔진 개발 · 렌더링·물리 시스템**
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

**개발 환경:** C++·doodle framework. 3인 팀에서 공통 객체·충돌 시스템을 담당하고 게임 로직에 통합했습니다. 팀 구성과 역할은 프로젝트 README에서 확인할 수 있습니다.

### OpenGL 렌더링·엔진 기초 — 개인 학습·구현

카메라·좌표 변환·텍스처·GLSL·렌더 상태를 다루며 FBO 렌더 패스를 확장하고 있습니다.

- 최신 작업은 별도 [LearnOpenGL 저장소](https://github.com/jaemin-lee00/LearnOpenGL)에서 확인할 수 있습니다.
- [공개된 초기 FBO 커밋](https://github.com/jaemin-lee00/LearnOpenGL/commit/8fbb710dfeab6817dd8c1b4ba2883e0e7e394484).
- FBO 자원 구성과 화면 출력 패스 확장을 진행 중입니다. 최근 로컬 작업과 공개 코드의 범위는 [OpenGL 개발 기록](https://app.notion.com/p/284e54fecb674ece807a04088aa0af0b)에 정리했습니다.

### IPTV 음성 인식·프로그램 통합 — Python

2024.11~2025.01, 5인 팀의 Client Programmer로 STT 기능과 웹 프로그램 통합을 담당했습니다.

- 메인 화면에 있던 STT 기능을 API로 분리하고 웹 프로그램과 연동했습니다.
- 음성 인식 기능과 다른 파트의 개발 결과를 연결해 시연용 통합 프로토타입을 제작했습니다.

- [역할·시연 영상·발표자료](https://app.notion.com/p/18532f9605b5808ebb78dee7c6ef3258)

## 이 저장소의 구성

| 경로 | 내용 |
|---|---|
| [GameProject](GameProject) | C++ 팀 게임 Dungeon Maker |
| [LearnOpenGL-VisualStudio](LearnOpenGL-VisualStudio) | 이전 OpenGL 학습 자료. 최신 작업은 별도 저장소 참고 |
| [ProjectH](ProjectH) | Unity 프로토타입 코드 |
| [OLC](OLC) | OneLoneCoder의 외부 엔진을 활용한 학습 자료 |

**외부 라이브러리 크레딧:** OLC는 OneLoneCoder 엔진을 활용한 학습 자료입니다. 외부 프레임워크·엔진의 저작권과 라이선스는 각 원문을 따릅니다.
