import glob

from PIL import Image


def main():
  # PPMファイルを名前順に取得
  ppm_files = sorted(glob.glob("out/img*.ppm"))

  # 最初の画像を開く
  images = [Image.open(f) for f in ppm_files]

  # GIFとして保存
  images[0].save(
    "output.gif",
    save_all=True,
    append_images=images[1:],
    duration=50,  # 1フレームあたりの表示時間(ms)
    loop=0,  # 0 = 無限ループ
  )


if __name__ == "__main__":
  main()
