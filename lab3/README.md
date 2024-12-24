# Лабораторная 3 – Деревья

Написать программу, которая будет применять указанный в варианте алгоритм к входным графам, заданным в файлах.  

То, как описаны графы в файлах, остаётся на выбор студента. Формат записи результата работы алгоритма в файл не регламентирован и устанавливается студентом.

В отчёте для каждого варианта требуется:
указать сложность алгоритма и доказать, что она именно такая;
объяснить почему был выбран тот или иной способ представления графов в программе.

## Вариант 1 –  Проверка свойства древочисленности (связность)

На вход программе подаётся граф. Проверить, является ли граф деревом по определению. 

Если нет, то в выходной файл написать, что нарушено: связность (в этом случае указать компоненты связности), ацикличность (в этом случае предоставить хотя бы один найденный цикл) или и то, и другое. В любом случае проверить, является ли граф древочисленным.

По итогу нужно запустить программу на различных графах и увидеть, что либо граф является деревом и древочисленный, либо то, что если ровно одно из условий из определения дерева не выполнено, то граф не будет древочисленным, либо то, что если оба условия не выполнены, то граф как может, так и не может быть древочисленным.

Здесь используются утверждения 1, 4 и 5 из теоремы параграфа “Основные свойства свободных деревьев”.