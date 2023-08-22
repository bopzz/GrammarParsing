Compile + Run instructions on terminal:
gcc -o main bits.c -Wall -Werror -std=c99
main

I made a small adjustment to the productions given by Professor Ferguson for easier use.

⟨E⟩ → ⟨T⟩ ⟨ET⟩
⟨ET⟩ → | ⟨E⟩ | ϵ
⟨T⟩ → ⟨F⟩ ⟨TT⟩
⟨TT⟩ → & ⟨T⟩ | ϵ
⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
⟨S⟩ → ⟨B⟩ ⟨ST⟩
⟨ST⟩ → ⟨S⟩ | ϵ
⟨B⟩ → 0 | 1

Changed to 

⟨E⟩ → ⟨T⟩ ⟨Z⟩
⟨Z⟩ → | ⟨E⟩ | ϵ
⟨T⟩ → ⟨F⟩ ⟨Y⟩
⟨Y⟩ → & ⟨T⟩ | ϵ
⟨F⟩ → ~ ⟨F⟩ | ( ⟨E⟩ ) | ⟨S⟩
⟨S⟩ → ⟨B⟩ ⟨X⟩
⟨X⟩ → ⟨S⟩ | ϵ
⟨B⟩ → 0 | 1

i.e. X = ST, Y = TT, Z = ET 

I also combined two parsing method into 1 run for your convenience.