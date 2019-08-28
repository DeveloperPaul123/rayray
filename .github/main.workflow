workflow "on push" {
  on = "push"
  resolves = ["GitHub Action for cpplint"]
}

action "GitHub Action for cpplint" {
  uses = "cclauss/GitHub-Action-for-cpplint@master"
  args = "cpplint --recursive ."
}
