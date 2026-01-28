import glob
import os

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

  # PNG形式で保存
  os.makedirs("out/png", exist_ok=True)

  for i, image in enumerate(images):
    # PPMファイル名から対応するPNGファイル名を生成
    ppm_filename = ppm_files[i]
    png_filename = os.path.basename(ppm_filename).replace(".ppm", ".png")
    path = os.path.join("out/png", png_filename)
    image.save(path)


if __name__ == "__main__":
  main()
