import random
def main():
    num = 1
    num_list = []
    for i in range(random.randint(10,25)):
        num = random.randint(0,500)
        num_list.append(num)
    print(num_list)


main()

