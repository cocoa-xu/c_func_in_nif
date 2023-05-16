defmodule CFuncInNifTest do
  use ExUnit.Case
  doctest CFuncInNif

  test "greets the world" do
    assert CFuncInNif.hello() == :world
  end
end
