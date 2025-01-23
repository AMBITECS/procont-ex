### Todo
queue to `In progress...`
редактирование множественного соединения на выходах. 


### In progress...


#### on pause


### Done ✓
- ...
- edit components instance names and update it in the interface. (without tests)
- Реализовать в `CBlock` сохранение типов входных/выходных/вх.вых. переменных в теге `addData`
- Полная поддержка drag-drop выбранных объектов (без множественного выбора)
- realize `localId` to get current max `localId` everywhere. Seems to be `extern`.
- undo/redo via `Qt's Undo Framework` (с добавлением функционала undo/redo будет пополняться)
- graphical connecting components.
- тёмная и светлая темы. Определяется автоматически. Выставлять вручную нельзя (пока)
- реализовать сохранение диаграммы и интерфейса посредством сигналов главного виджета
- new/edit/reset variables on the components inputs/outputs
- mouse wheel <Ctrl> - scrolling vertical/horizontal
- удалить сохранение в файл текущего POU
- если пользователь удалил блок, то вот вам данные для удаления соответствующей переменной
- put POUs into the `components palette`

### не забыть
 очень тонкий момент - в программе никак не отражен тот факт, что CBody в одном POU может быть несколько 
 (по стандарту, но не факт что так будет)