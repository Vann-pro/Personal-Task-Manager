#pragma once
// Manajemen tugas: CRUD, validasi, filter, pengurutan, statistik, ekspor/impor.
#include <string>
#include <vector>

#include "task.h"

namespace ptm {

struct Result {
  bool ok = true;
  std::string error;
  int id = 0;
  int count = 0;
};

std::string resultToJson(const Result& r);

class TaskManager {
 public:
  // Memuat data tersimpan (mengganti seluruh isi). Teks kosong = daftar kosong.
  // Jika gagal, data yang sedang ada TIDAK berubah.
  Result load(const std::string& text, int64_t now);
  // mode: 0 = hanya validasi, 1 = ganti semua, 2 = gabungkan. Atomik: gagal = tidak ada perubahan.
  Result importData(const std::string& text, int mode, int64_t now);
  Result add(const std::string& text, int64_t now);
  Result update(const std::string& text, int64_t now);
  Result remove(int id);

  std::string get(int id, int64_t now) const;
  std::string query(const std::string& filterJson, int64_t now) const;
  std::string stats(int64_t now) const;
  // Tugas belum selesai yang deadline-nya dalam windowMs ke depan (urut deadline) + jumlah yang terlambat.
  std::string upcoming(int64_t now, int64_t windowMs) const;
  // Jumlah deadline per hari dalam satu bulan. tzOffsetMin = menit zona waktu lokal dari UTC (WIB = 420).
  std::string calendar(int year, int month, int tzOffsetMin, int64_t now) const;
  // Dokumen JSON untuk penyimpanan dan ekspor (tanpa field hasil hitung).
  std::string serialize(int64_t now) const;
  size_t size() const { return tasks_.size(); }

 private:
  std::vector<Task> tasks_;
  int nextId_ = 1;
};

}  // namespace ptm
