package dev.natdorshimer.cmpsc

fun main() {
  val skirmishHandler = SkirmishHandler(
    maxAttackerDice =  3,
    maxDefenderDice = 2
  )

  while (true) {
    val initialData = getSkirmishDataFromUser()
    val skirmishOption = getSkirmishOptionFromUser()

    if (skirmishOption is SkirmishOption.Withdraw) {
      println("You have chosen to withdraw from the battle.\n")
      continue
    }

    val result = skirmishHandler.skirmish(initialData, skirmishOption)
    printResults(initialData, result)

    if (getShouldQuitFromUser()) {
      break
    }
  }
}

private sealed class SkirmishOption {
  object Attack: SkirmishOption()
  object AttackUntilDefeated: SkirmishOption()
  class AttackUntilRemaining(val attackersRemaining: Int): SkirmishOption()
  object Withdraw: SkirmishOption()
}

private class SkirmishHandler(
  private val maxAttackerDice: Int,
  private val maxDefenderDice: Int,
) {
  private fun simpleSkirmish(skirmishData: SkirmishData): SkirmishData {
    val attackerDice = skirmishData.attackerSize.coerceAtMost(maxAttackerDice)
    val defenderDice = skirmishData.defenderSize.coerceAtMost(maxDefenderDice)

    val attackerRolls = (1..attackerDice).map { (1..6).random() }.sortedDescending()
    val defenderRolls = (1..defenderDice).map { (1..6).random() }.sortedDescending()

    val diceToCompare = attackerRolls.zip(defenderRolls)
    val attackerLosses = diceToCompare.count { (attacker, defender) ->
      attacker <= defender
    }

    val defenderLosses = diceToCompare.size - attackerLosses
    return SkirmishData(
      skirmishData.attackerSize - attackerLosses,
      skirmishData.defenderSize - defenderLosses,
    )
  }

  private fun skirmishWhile(skirmishData: SkirmishData, condition: (SkirmishData) -> Boolean): SkirmishData {
    var skirmishData = skirmishData
    while(condition(skirmishData)) {
      skirmishData = simpleSkirmish(skirmishData)
    }
    return skirmishData
  }

  fun skirmish(skirmishData: SkirmishData, option: SkirmishOption): SkirmishData {
    return when (option) {
      is SkirmishOption.Attack -> simpleSkirmish(skirmishData)

      is SkirmishOption.AttackUntilDefeated -> skirmishWhile(skirmishData) {
        it.attackerSize > 0 && it.defenderSize > 0
      }

      is SkirmishOption.AttackUntilRemaining -> skirmishWhile(skirmishData) {
        it.attackerSize >= option.attackersRemaining && it.defenderSize > 0
      }

      else -> SkirmishData(0, 0)
    }
  }
}

private class SkirmishData(
  val attackerSize: Int,
  val defenderSize: Int,
)

private fun getShouldQuitFromUser(): Boolean {
  print("Would you like to continue? (y/n) ")
  val input = readLine()!!.lowercase()
  return input != "y"
}

private fun getSkirmishDataFromUser(): SkirmishData {
  print("Please input attacker size: ")
  val attackerSize = getIntegerFromUser()

  print("Please input defender size: ")
  val defenderSize = getIntegerFromUser()

  println()

  return SkirmishData(attackerSize, defenderSize)
}

private fun printResults(initialData: SkirmishData, result: SkirmishData) {
  println("Attacker size after battle: ${result.attackerSize}")
  println("Attacker losses: ${initialData.attackerSize - result.attackerSize}")

  println("Defender size after battle: ${result.defenderSize}")
  println("Defender losses: ${initialData.defenderSize - result.defenderSize}")

  println()
}

private fun getIntegerFromUser(): Int {
  while(true) {
    try {
      return readLine()!!.toInt()
    } catch (e: NumberFormatException) {
      println("Invalid input, please try again.")
    }
  }
}

private fun getSkirmishOptionFromUser(): SkirmishOption {
  println("Please choose one of the following:")

  println("1. Attack")
  println("2. Attack until one army is defeated")
  println("3. Attack until attacking armies have __ left")
  println("4. Withdraw from the battle")

  print("Option: ")

  return when (getIntegerFromUser()) {
    1 -> SkirmishOption.Attack
    2 -> SkirmishOption.AttackUntilDefeated
    3 -> {
      print("Please input remaining attackers: ")
      val remainingAttackers = readLine()!!.toInt()

      SkirmishOption.AttackUntilRemaining(remainingAttackers)
    }
    else -> SkirmishOption.Withdraw
  }
}