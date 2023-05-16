defmodule CFunc do
  @moduledoc false
  def pointer_to_my_add do
    CFunc.Nif.pointer_to_my_add()
  end

  def new_struct(mode, a, b) do
    CFunc.Nif.new_struct(mode, a, b)
  end

  def free_struct(ptr) do
    CFunc.Nif.free_struct(ptr)
  end
end
