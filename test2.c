#include "types.h"
#include "stat.h"
#include "user.h"

#define NUM_PROC 3
#define LOOP_COUNT 50

void cpu_bound(void) {
  int i, j;
  for (i = 0; i < LOOP_COUNT; i++) {
    for (j = 0; j < LOOP_COUNT; j++) {
      // 계산 작업
    }
    printf(1, "[PID %d] CPU Burst %d finished\n", getpid(), i + 1);
  }
  exit();
}

void io_bound(void) {
  int i;
  for (i = 0; i < LOOP_COUNT; i++) {
    sleep(10);  // I/O 작업 시뮬레이션 (10 ticks)
    printf(1, "[PID %d] I/O Burst %d finished\n", getpid(), i + 1);
  }
  exit();
}

void long_running(void) {
  int i;
  for (i = 0; ; i++) {
    // 무한 루프
  }
}

int main(void) {
  int i, pid;

  printf(1, "Starting xv6 Scheduler Test...\n");

  // CPU-bound 프로세스 생성
  for (i = 0; i < NUM_PROC; i++) {
    pid = fork();
    if (pid == 0) {
      cpu_bound();
    } else if (pid < 0) {
      printf(1, "fork failed\n");
      exit();
    }
  }

  // I/O-bound 프로세스 생성
  for (i = 0; i < NUM_PROC; i++) {
    pid = fork();
    if (pid == 0) {
      io_bound();
    } else if (pid < 0) {
      printf(1, "fork failed\n");
      exit();
    }
  }

  // Long-running 프로세스 생성 (CPU 점유 시간 제한 테스트용)
  pid = fork();
  if (pid == 0) {
    long_running();
  } else if (pid < 0) {
    printf(1, "fork failed\n");
    exit();
  }

  // 모든 자식 프로세스가 종료될 때까지 대기
  for (i = 0; i < NUM_PROC * 2 + 1; i++) {
    wait();
  }

  printf(1, "All processes finished.\n");
  exit();
}