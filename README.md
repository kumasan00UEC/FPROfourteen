# 基礎プログラミング演習第14回総合演習

![メネラウスの定理](menelaus.jpeg)

## 作成gif

QuizKnockのアイキャッチ

## メンバー

- s2512125 角谷拓武
- t2512145 田中琉登
- m2512225 宮崎昭徳

## 使用方法

### `git`の使い方

リモートの変更をローカルに取得したい時

```sh
git pull
```

ローカルの変更をリモートに共有したい時

```sh
git add .
git commit -m "コミットメッセージ"
git push origin main
```

### c言語のコンパイル法

```sh
gcc animate1.c img.c -lm -o animate.out

./animate.out
```

### `ppm`から`gif`

ローカル

```sh
uv run main.py
```

リモート

```sh
animate out/img*.ppm &
```

or

```sh
convert -delay 5 out/img*.ppm animate1.gif
eog animate1.gif &
```
