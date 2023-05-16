defmodule CFunc do
  @moduledoc false
  def pointer_to_my_add do
    CFunc.Nif.pointer_to_my_add()
  end
end
