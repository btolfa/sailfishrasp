# Suburban Trains - Расписание электричек под Sailfish OS

## Описание файлов QML
- qml/harbour-subtrains.qml - корневой qml приложения
- qml/cover/CoverPage.qml - Cover приложения
- qml/pages/AboutPage.qml - страница "О программе"
- qml/pages/FirstPage.qml - начальная страница приложения (где показывается регион, дата, поиск и т.п.)
- qml/pages/ThreadsPage.qml - страница с маршрутами по направлению, где показаны электрички с необходимым маршрутом.
                          Разумеется, начальные и конечные станции маршрутов электрички могут не совпадать
                          с выбранными станциями, однако в этом случае маршрут содержит в себе выбранные станции в правильном порядке.)
- qml/pages/ThreadInfo.qml - страница с названиями и временными интервалами остановок выбранного маршрута
- qml/pages/ZonePage.qml - страница с выбором пригородной зоны

## Светлое будущее
- [ ] Если искались поезда на сегодня, то на **Cover** выводим ближайший поезд и кнопку обновить, иначе скриншот
- [ ] Избранные или последние маршруты
- [ ] Оффлайн расписание?
- [ ] Проверять актуальность базы (смотреть `ETag`?) Если старая, то скачать XML, превратить в **sqlite** и обновить