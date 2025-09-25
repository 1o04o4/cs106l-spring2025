class TwoNum {
 public:
  TwoNum(int a, int b);
  TwoNum();

  int get_a() const;
  int get_b() const;

  void set_a(int value);
  void set_b(int value);

 private:
  bool is_equal() const;
  int _a, _b;
};