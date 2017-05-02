# MetalSlug3Imitation
메탈슬러그3 모작

## 리소스 파일
리소스 파일은 개인 dropbox 저장공간에서 관리하였다.
소스코드에서 리소스 파일에 접근하기 하는 경로를 유연하게 변경하기 위해서 메탈슬러그 관련 리소스들을 저장하고 있는 폴더로 연결되는 Symlink를 `Resource`라는 이름으로 솔루션 폴더에 생성하여 사용한다.
이렇게 하면 리소스 경로가 변경되더라도 `Resource` Symlink만 수정해주면 ok다.

### Symlink 만들기
C:\Users\Foo\Desktop\MetalSlug3Imitation(솔루션 경로)에 D:\cloud\Drobox\Portfolio\MetalSlug3\Resource로 연결되는 Resource라는 Symlink를 생성한다.
```
mklink /j "C:\Users\Foo\Desktop\MetalSlug3Imitation\Resource" D:\cloud\Drobox\Portfolio\MetalSlug3\Resource
```
