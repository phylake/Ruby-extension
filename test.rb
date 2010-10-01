#require 'my_test'
require 'matrices'
include Matrices
require 'test/unit'
class MatrixTest < Test::Unit::TestCase
  def test_test
    x = 2
    y = 3
    theta = 45
    
    dx = x*Math.cos(theta) + y*Math.sin(theta)
    dy = -x*Math.sin(theta) + y*Math.cos(theta)
    
    assert_equal( [dx,dy], rotate([x,y], theta) )
  end
end