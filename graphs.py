import matplotlib.pyplot as plt 

i = 0

with open('values.txt', 'r') as f:
    line = f.readlines()

k = len(line)

time=[0]*(k-1)
mean_anomaly=[0]*(k-1)
eccentric_anomaly=[0]*(k-1)
true_anomaly=[0]*(k-1)

for j in range (0, 4):
    for x in range (0, k-1):
        string = line[x+1].split()
        if (j==0):
            time[x] = float(string[0])
        if (j==1):
            mean_anomaly[x] = float(string[1])
        if (j==2):
            eccentric_anomaly[x] = float(string[2])
        if (j==3):
            true_anomaly[x] = float(string[3])

x = time

y = mean_anomaly
#y1 = eccentric_anomaly
#y2 = true_anomaly

plt.plot(x, y, color='green')
#plt.plot(x, y1, color='green')
#plt.plot(x, y2, color='green')

plt.xlabel('Время t [c]') #Подпись для оси х

plt.ylabel('Средняя аномалия M(t) [рад]') #Подпись для оси y
#plt.ylabel('Эксцентрическая аномалия E(t) [рад]') #Подпись для оси y
#plt.ylabel('Истинная аномалия Theta(t) [рад]') #Подпись для оси y

plt.title('Метод итераций. Зависимость средней аномалии от времени') #Название
#plt.title('Метод итераций. Зависимость эксцентрической аномалии от времени') #Название
#plt.title('Метод итераций. Зависимость истинной аномалии от времени') #Название

#plt.title('Метод половинного деления. Зависимость средней аномалии от времени') #Название
#plt.title('Метод половинного деления. Зависимость эксцентрической аномалии от времени') #Название
#plt.title('Метод половинного деления. Зависимость истинной аномалии от времени') #Название

#plt.title('Метод золотого сечения. Зависимость средней аномалии от времени') #Название
#plt.title('Метод золотого сечения. Зависимость эксцентрической аномалии от времени') #Название
#plt.title('Метод золотого сечения. Зависимость истинной аномалии от времени') #Название

#plt.title('Метод Ньютона. Зависимость средней аномалии от времени') #Название
#plt.title('Метод Ньютона. Зависимость эксцентрической аномалии от времени') #Название
#plt.title('Метод Ньютона. Зависимость истинной аномалии от времени') #Название


plt.show()