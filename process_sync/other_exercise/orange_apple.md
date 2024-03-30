# Problem Description

There is a plate on the table. Dad could put apple on the table, mom could put orange on the table. son eats apple, daughter eats orange. Notice there could be only one fruit in the plate.

```cpp
semaphore hasApple = 0;
semaphore hasOrange = 0;
semaphore emptyPlate = 1;

void dad(){
    while(true){
        wait(emptyPlate);
        putAppleIntoPlate();
        signal(hasApple);
    }
}

void mom(){
    while(true){
        wait(emptyPlate);
        putOrangeIntoPlate();
        signal(hasOrange);
    }
}

void son(){
    while(true){
        wait(hasApple);
        eat();
        signal(emptyPlate);
    }
}

void daughter(){
    while(true){
        wait(hasOrange);
        eat();
        signal(emptyPlate);
    }
}

int main(){
    cobegin
    dad();
    mom();
    son();
    daughter();
    coend
}
```

