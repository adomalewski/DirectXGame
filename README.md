# DirectXGame

DX scena:
1.mapa
-elementy dogrywane gdy user jest w pobliżu
-niektore elementy widoczne z daleka (dokładność zależna od odległości lub ruchoma textura tła)
-minimalna dokładność elementów lub ich brak
-tryb wplywający na mape np pora dnia, warunki pogodowe
2.scenariusz
3.zadanie - wykonane zadanie powoduje zmiane możliwych wyświetlanych elementów na scenie
4.atrybuty postaci (np włączone magiczne pierścienie wokół postaci)
5.wygląd postaci (np ma miecz)
6.poziom trudności (może wpływać na ilość przeciwników, niedostępność pewnych prostych przejść)
7.położenie postaci na mapie

zawartość scenariusza:
1.mapy i ich kolejność w grze
2.zadania na mapie oraz wszystkie punkty startowe i końcowe na danej mapie wraz z ich kolejnością, może być też czas na wykonanie danego zadania
3.zdarzenia i dodatkowe elementy na mapie - co ma sie pojawić/dograć na mapie gdy postać jest w pobliżu, może to też zależeć od poziomu trudności (np mają sie dograć przeciwnicy w określonej ilości)

zawartość zadania:
1.warunki do pojawienia sie zadania
2.warunki spełnienia zadania (czas, przejście do danego położenia/rejonu na danej mapie)
3.właściwości które wpływają na mape (np pojawia się boss)
4.właściwości które wpływają na postać

typy scen:
1.scena2D (menu główne - gry, hud, menu postaci, kursor (dla niekonsolowych); w tych elementach będzie wykorzystywany textTool, textureTool, userControls (reagowanie na klawiature, myszke, dla pól tekstowych wpisywanie - korzystanie z textTool))
2.scena3D (kursor opcjonalnie (dla niekonsolowych), kamera/kamery i tryb kamery postaci, sterowanie)

dodatkowe ustalenia:
-każda scena odświeżana jest co frame
-podczas ruchu kamery/postaci dokładność elementów może spadać (im szybszy ruch tym mniejsza ilość szczegółów)
-nie renderowanie niewidocznych elementów (3D), określenie strefy widoczności (dynamiczne) i elementów w tej strefie
-TimerManager do zarządzania timerami TimerData (obserwator/wizytator)
-utworzenie SceneElement
-przyda sie klasa CommonShaderManager dla shaderów które mogą być wykorzystane przez różne elementy graficzne
-należy używać najlepszy możliwy i właściwy shader do danej sytuacji (np do wyświetlenia textu 2D w prosty sposob na ekranie należy użyć najprostszego shadera)
-trzeba pamiętać że textClass do 2D może miec wspolny shader co bitmapClass (zwykły najprostszy) ale i trudniejszy do obrotów z macierzą world

nurtujące pytania:
1.czy powinien być osobny scenariusz na scene 2D i 3D?
2.co powinna zawierać klasa scenariusza?
3.czy scenariusz powinien być per mape?
4.czy elementy graficzne powinny w sobie zawierać tworzenie shadera? co jeśli ten shader ma byc jeszcze gdzieś indziej wykorzystany, a może od tego uzależnić wybór czy tworzyć shader w elementcie czy w managerze shaderów?
5.jak zarządzać i w co umieszczać elementy na scenie by je kontrolować?
6.co z modelami? może powrzucać je do osobnego folderu

zmiana nazw klas/plików/obiektów (fajne słowa: Aggregator, Consolidator, Service, User, Interaction):
d3dclass - D3DEngine/D3DCore
cameraclass - D3DCamera
bitmapclass - D3DBitmap
fontclass - D3DFont
graphicsclass - D3DUserGraphicConsolidator
inputclass - DXUserInput
lightclass - D3DLight
modelclass - D3DModel
systemclass - WindowGameSystem
textclass - D3DText
textureclass - D3DTexture
Scene3Dclass - DXScene3D
Scene2Dclass - DXScene2D
